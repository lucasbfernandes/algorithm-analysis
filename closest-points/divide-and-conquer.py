#!/usr/bin/env python

import random
import math
import sys

INFINITY = 20000000

class Point:
	def __init__(self, x, y):
		self.x = x
		self.y = y

def generatePoints(numberOfPoints):
	return [Point(random.randint(0, 1000), random.randint(0, 1000)) for i in range(numberOfPoints)]

def getPointDistance(pointA, pointB):
	return math.sqrt(
		(pointA.x - pointB.x) * (pointA.x - pointB.x) +
		(pointA.y - pointB.y) * (pointA.y - pointB.y)
	)

def getMiddlePointsMinimum(middlePointsList, minimum):
	minimumPoints = None
	for i in range(len(middlePointsList)):
		for j in range(i + 1, len(middlePointsList)):
			if (middlePointsList[j].y - middlePointsList[i].y) >= minimum:
				break
			elif getPointDistance(middlePointsList[i], middlePointsList[j]) < minimum:
				minimumPoints = (middlePointsList[i], middlePointsList[j])
				minimum = getPointDistance(middlePointsList[i], middlePointsList[j])
	return (minimumPoints, minimum)

def getMiddlePointsList(ySortedList, left, right, middlePoint, minimum):
	middlePointsList = []
	for i in range(left, right):
		if (abs(ySortedList[i].x - middlePoint.x) < minimum):
			middlePointsList.append(ySortedList[i])
	return middlePointsList

def computeShortestDistanceBetweenPoints(xSortedList, ySortedList, left, right):
	if abs(right - left) == 2:
		return ((ySortedList[left], ySortedList[right - 1]), getPointDistance(ySortedList[left], ySortedList[right - 1]))

	if abs(right - left) == 1:
		return ((ySortedList[left], ySortedList[left]), INFINITY)

	middle = (left + right) / 2
	(leftPoints, leftMinimum) = computeShortestDistanceBetweenPoints(xSortedList, ySortedList, left, middle)
	(rightPoints, rightMinimum) = computeShortestDistanceBetweenPoints(xSortedList, ySortedList, middle, right)

	minimum = min(leftMinimum, rightMinimum)
	minimumPoints = leftPoints if (minimum == leftMinimum) else rightPoints

	middlePointsList = getMiddlePointsList(ySortedList, left, right, xSortedList[middle], minimum)
	(middlePoints, middleMinimum) = getMiddlePointsMinimum(middlePointsList, minimum)
	minimumPoints = minimumPoints if (min(minimum, middleMinimum) == minimum) else middlePoints

	return (minimumPoints, min(minimum, middleMinimum))

def getShortestDistanceBetweenPoints(pointsList):
	xSortedList = sorted(pointsList, key=lambda point: point.x, reverse=False)
	ySortedList = sorted(pointsList, key=lambda point: point.y, reverse=False)
	return computeShortestDistanceBetweenPoints(xSortedList, ySortedList, 0, len(pointsList))

def getStdinPointsList():
	pointsList = []
	for line in sys.stdin:
		splittedLine = str.split(line)
		pointsList.append(Point(int(splittedLine[0]), int(splittedLine[1])))
	return pointsList

def getRandomPointsList():
	numberOfPoints = int(input())
	return generatePoints(numberOfPoints)

def getPointsList():
	#return getRandomPointsList()
	return getStdinPointsList()

def main():
	pointsList = getPointsList()
	shortestDistanceTuple = getShortestDistanceBetweenPoints(pointsList)

	print("Points:")
	for i in range(len(pointsList)):
		print(pointsList[i].x, pointsList[i].y)

	print("\nShortest distance points:")
	print(shortestDistanceTuple[0][0].x, shortestDistanceTuple[0][0].y)
	print(shortestDistanceTuple[0][1].x, shortestDistanceTuple[0][1].y)

	print("\nShortest distance:")
	print(shortestDistanceTuple[1])

if __name__ == '__main__':
	main()

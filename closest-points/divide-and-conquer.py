#!/usr/bin/env python

import random
import math

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

def getMiddlePointsMinimum(middlePoints, minimum):
	for i in range(len(middlePoints)):
		for j in range(i + 1, len(middlePoints)):
			if (middlePoints[j].y - middlePoints[i].y) >= minimum:
				break
			elif getPointDistance(middlePoints[i], middlePoints[j]) < minimum:
				minimum = getPointDistance(middlePoints[i], middlePoints[j])
	return minimum

def getMiddlePoints(ySortedList, left, right, middlePoint, minimum):
	middlePoints = []
	for i in range(left, right):
		if (abs(ySortedList[i].x - middlePoint.x) < minimum):
			middlePoints.append(ySortedList[i])
	return middlePoints

def computeShortestDistanceBetweenPoints(xSortedList, ySortedList, left, right):
	if abs(right - left) == 2:
		return getPointDistance(ySortedList[left], ySortedList[right - 1])

	if abs(right - left) == 1:
		return INFINITY

	middle = (left + right) / 2
	leftMinimum = computeShortestDistanceBetweenPoints(xSortedList, ySortedList, left, middle)
	rightMinimum = computeShortestDistanceBetweenPoints(xSortedList, ySortedList, middle, right)
	minimum = min(leftMinimum, rightMinimum)
	middlePoints = getMiddlePoints(ySortedList, left, right, xSortedList[middle], minimum)
	return min(minimum, getMiddlePointsMinimum(middlePoints, minimum))

def getShortestDistanceBetweenPoints(pointsList):
	xSortedList = sorted(pointsList, key=lambda point: point.x, reverse=False)
	ySortedList = sorted(pointsList, key=lambda point: point.y, reverse=False)
	return computeShortestDistanceBetweenPoints(xSortedList, ySortedList, 0, len(pointsList))

def main():
	numberOfPoints = int(input())
	pointsList = generatePoints(numberOfPoints)
	shortestDistance = getShortestDistanceBetweenPoints(pointsList)

	for i in range(len(pointsList)):
		print(pointsList[i].x, pointsList[i].y)

	print("Shortest distance: ", shortestDistance)

if __name__ == '__main__':
	main()

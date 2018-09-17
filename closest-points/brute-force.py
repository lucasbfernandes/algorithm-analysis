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

def getShortestDistanceBetweenPoints(pointsList):
	minimum = INFINITY
	minimumPoints = None
	for i in range(len(pointsList)):
		for j in range(i + 1, len(pointsList)):
			if getPointDistance(pointsList[i], pointsList[j]) < minimum:
				minimumPoints = (pointsList[i], pointsList[j])
				minimum = getPointDistance(pointsList[i], pointsList[j])
	return (minimumPoints, minimum)

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

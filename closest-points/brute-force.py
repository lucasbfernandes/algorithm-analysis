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

def getShortestDistanceBetweenPoints(pointsList):
	minimum = INFINITY
	minimumPoints = None
	for i in range(len(pointsList)):
		for j in range(i + 1, len(pointsList)):
			if getPointDistance(pointsList[i], pointsList[j]) < minimum:
				minimumPoints = (pointsList[i], pointsList[j])
				minimum = getPointDistance(pointsList[i], pointsList[j])
	return (minimumPoints, minimum)

def main():
	numberOfPoints = int(input())
	pointsList = generatePoints(numberOfPoints)
	shortestDistanceTuple = getShortestDistanceBetweenPoints(pointsList)

	for i in range(len(pointsList)):
		print(pointsList[i].x, pointsList[i].y)

	print("Shortest distance points: ")
	print(shortestDistanceTuple[0][0].x, shortestDistanceTuple[0][0].y)
	print(shortestDistanceTuple[0][1].x, shortestDistanceTuple[0][1].y)
	print("Shortest distance: ", shortestDistanceTuple[1])

if __name__ == '__main__':
	main()

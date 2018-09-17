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
	for i in range(len(pointsList)):
		for j in range(i + 1, len(pointsList)):
			if getPointDistance(pointsList[i], pointsList[j]) < minimum:
				minimum = getPointDistance(pointsList[i], pointsList[j])
	return minimum

def main():
	numberOfPoints = int(input())
	pointsList = generatePoints(numberOfPoints)
	shortestDistance = getShortestDistanceBetweenPoints(pointsList)

	for i in range(len(pointsList)):
		print(pointsList[i].x, pointsList[i].y)

	print("Shortest distance: ", shortestDistance)

if __name__ == '__main__':
	main()

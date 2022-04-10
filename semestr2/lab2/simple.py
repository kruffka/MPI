import random

routes = []


def find_paths(node, cities, path, distance):
    # Add way point
    path.append(node)

    # Calculate path length from current to last node
    if len(path) > 1:
        distance += cities[path[-2]][node]

    # If path contains all cities and is not a dead end,
    # add path from last to first city and return.
    if (len(cities) == len(path)) and (path[0] in cities[path[-1]]):
        global routes
        path.append(path[0])
        distance += cities[path[-2]][path[0]]
        # print (path, distance)
        routes.append([distance, path])
        return

    # Fork paths for all possible cities not yet used
    for city in cities:
        if (city not in path) and (node in cities[city]):
            find_paths(city, dict(cities), list(path), distance)


if __name__ == '__main__':
    cities = {}

    N = 13
    # 2 3 4 5 6      7          8          9         10        11         12            13
    # 0 0 0 0 0.0009 0.000999   0.008998   0.070996  0.881000  09.602000  01.46.031000  15.23.201000
    array = [[random.randint(50, 250) for x in range(N)] for y in range(N)]

    for i in range(N):
        for j in range(N):
            array[i][j] = array[j][i]
            if (i == j):
                array[i][j] = 0

    # array = [[0, 10, 15, 20],
    #          [10, 0, 35, 25],
    #          [15, 35, 0, 30],
    #          [20, 25, 30, 0]]


    for i in range(N):
        print(array[i])
        cities[chr(65 + i)] = chr(65 + i)

    for i in range(N):

        cities_small = {chr(65 + j) : array[i][j] for j in range(N)}
        del cities_small[chr(65 + i)]
        # print(cities_small)

        cities[chr(65 + i)] = cities_small


    # for i in range(N):
    #     print(cities[chr(65 + i)])

    print("Start: A")

    from datetime import datetime

    start_time = datetime.now()

    find_paths('A', cities, [], 0)

    time_elapsed = datetime.now() - start_time

    print('Time elapsed (hh:mm:ss.ms) {}'.format(time_elapsed))

    # print("\n")
    # routes.sort()
    # if len(routes) != 0:
    #     print("Shortest route: %s" % routes[0])
    # else:
    #     print("FAIL!")
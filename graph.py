#Current just a stub
class Graph:
    def __init__(self, graph=None):
        self.name = "default"
        if graph == None:
            graph = {}
        
        self.__graph = graph

    def getStartState():
        return self.__graph.items()[0].key

    def getSuccessors():
        #just a stub
        return ["one", "two", "three"]

    def vertices(self):
        return list(self.__graph.keys())

    def edges(self):
        return self.__generate_edges()

    def __generate_edges(self):
        edges = []
        for vertex in self.__graph:
            for neighbour in self.__graph[vertex]:
                if {neighbour, vertex} not in edges:
                    edges.append({vertex, neighbour})
        return edges

    def add_edge(self, edge):
        edge = set(edge)
        (vertex1, vertex2) = tuple(edge)
        if vertex1 in self.__graph:
            self.__graph[vertex1].append(vertex2)
        else:
            self.__graph[vertex1] = [vertex2]
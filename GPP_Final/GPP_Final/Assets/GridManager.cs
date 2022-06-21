﻿using UnityEngine;
using System.Collections;
//using UnityEditor;
using System.Collections.Generic;
using System.Linq;

public class GridManager : MonoBehaviour {
    public enum TileType {
        Plain,
        Wall
    }
    static TileType[] world = null;
    static int n_x = 5;
    static int n_z = 5;

    static Vector3[] corners = { new Vector3(1, -0, 0), new Vector3(0, 0, 1) };

    public Transform player;
    public Transform plane;
    public GameObject enemy;

    private void Start() {
        if (player == null)
            player = GameObject.Find("Player").transform;

        Instantiate(enemy);
        enemy.GetComponent<Enemy>().player = player;

        BuildWorld(25, 25);
    }

    public static Vector3 locateToCenter(Vector3 pos)
    {
        return pos + new Vector3(0.5f, 0, 0.5f);
    }

    public static void SetAsWall(Vector3 pos)
    {
        world[pos2Cell(pos)] = TileType.Wall;
    }

    public static void SetAsNotWall(Vector3 pos) {
        world[pos2Cell(pos)] = TileType.Plain;
    }

    public void BuildWorld(int n_rows, int n_cols)
    {
        int max_tiles = n_rows * n_cols;

        n_x = n_rows;
        n_z = n_cols;

        // set up the player's position to the center of the grid.
        player.position = locateToCenter(new Vector3(n_x / 2, 0.5f, n_z / 2)); // place the player to the center.
        plane.position = player.position + Vector3.down;
        plane.localScale = new Vector3(n_x * 0.1f, plane.localScale.y, n_z * 0.1f);
        enemy.transform.position = player.position + plane.localScale * 2f;
        int player_cell = pos2Cell(player.transform.position);

        // construct a game world and assign walls.
        world = new TileType[max_tiles];
        for (int i = 0; i < max_tiles; i++)
        {
            world[i] = TileType.Plain;
            if (i == player_cell) continue; // we assign the player's location as a plain grid cell.

            /*
            if (Random.Range(0.0f, 1.0f) < 0.25) // wall is created with a probability of 25 %.
            {
                world[i] = TileType.Wall;
                var wall = GameObject.CreatePrimitive(PrimitiveType.Cube);
                wall.GetComponent<MeshRenderer>().material.color = Color.yellow;
                wall.tag = "Wall";
                wall.transform.position = locateToCenter(cell2Pos(i));
            }
            */
        }

        for (int i = 0; i < max_tiles; i++) drawRect(i, world[i] == TileType.Wall ? Color.black : Color.green);

        transform.position = player.position + new Vector3(0, n_z*Mathf.Sqrt(2), 0); // locate camera properly.
        transform.LookAt(player);
        transform.RotateAround( player.position, new Vector3(-1, 0, 0), 50);
        transform.RotateAround( player.position, new Vector3(0, -1, 0), 52);
    }

    public static int pos2Cell(Vector3 pos)
    {
        return ((int)pos.z) * n_x + (int)pos.x;
    }

    public static Vector3 cell2Pos(int cellno)
    {
        return new Vector3(cellno % n_x, 0, cellno / n_x);
    }

    public static Vector3 pos2center(Vector3 pos)
    {

        return locateToCenter(cell2Pos(pos2Cell(pos)));
    }

    public static void drawRect(int cellno, Color c, float duration=10000.0f)
    {
        Vector3 correction = new Vector3(0, -0.5f, 0);
        Vector3 lb = cell2Pos(cellno) + correction;
        

        Debug.DrawLine(lb, lb + corners[0], c, duration);
        Debug.DrawLine(lb, lb + corners[1], c, duration);
        Vector3 rt = lb + corners[0] + corners[1] + correction;
        Debug.DrawLine(rt, rt - corners[0], c, duration);
        Debug.DrawLine(rt, rt - corners[1], c, duration);
    }

    int[] findNeighbors(int cellno, TileType[] world)
    {
        List<int> neighbors = new List<int> { -1, 1, -n_x, n_x, -n_x - 1, -n_x + 1, n_x - 1, n_x + 1 };

        if (cellno % n_x == 0)          neighbors.RemoveAll( (no) => { return no == -1   || no == -1 - n_x || no == -1 + n_x; } );
        if (cellno % n_x == n_x - 1)    neighbors.RemoveAll( (no) => { return no ==  1   || no ==  1 - n_x || no ==  1 + n_x; } );
        if (cellno / n_x == 0)          neighbors.RemoveAll( (no) => { return no == -n_x || no == -n_x - 1 || no == -n_x + 1; } );
        if (cellno / n_x == n_z - 1)    neighbors.RemoveAll( (no) => { return no ==  n_x || no ==  n_x - 1 || no ==  n_x + 1; } );
        
        for (int i=0; i< neighbors.Count; )
        {
            neighbors[i] += cellno;
            if (neighbors[i] < 0 || neighbors[i] >= n_x * n_z || world[neighbors[i]] == TileType.Wall ) neighbors.RemoveAt(i);
            else i++; /* increase unless removing */
        }

        // remove crossing-neighbors if they are blocked by two adjacent walls. See ppt page 41.
        Vector3 X = cell2Pos(cellno);
        for (int i=0; i < neighbors.Count; )
        {
            Vector3 Xp = cell2Pos(neighbors[i]);
            if ( (X.x - Xp.x) * (X.z - Xp.z) != 0)
            {
                if ( world[ pos2Cell(new Vector3(Xp.x, 0, X.z))] == TileType.Wall 
                    && world[ pos2Cell(new Vector3(X.x, 0, Xp.z))] == TileType.Wall )
                {
                    neighbors.RemoveAt(i);
                    continue;
                }
            }
            i++;
        }
        return neighbors.ToArray();
    }

    int[] buildPath(int[] parents, int from, int to)
    {
        if (parents == null) return null;

        List<int> path = new List<int>();
        int current = to;
        while ( current != from )
        {
            path.Add(current);
            current = parents[current];
        }
        path.Add(from); // to -> ... -> ... -> from

        path.Reverse(); // from -> ... -> ... -> to
        return path.ToArray();
    }

    void drawPath(int[] path)
    {
        if (path == null) return;
        Vector3 correction = new Vector3(0, -0.5f, 0);

        for (int i=0; i< path.Length-1; i++)
        {
            Debug.DrawLine(locateToCenter(cell2Pos(path[i]))+correction , locateToCenter(cell2Pos(path[i + 1]))+correction, Color.blue, 5.0f);
        }
    }

    class Node
    {
        public int      no;
        public float    f; // final cost = global cost + heuristic cost
        public float    g; // global cost
    }

    public enum MethodType {  DFS, BFS, AStar };

    float computeDistance(int cell1, int cell2)
    {
        return Vector3.Distance(cell2Pos(cell1), cell2Pos(cell2));
    }

    public MethodType method = MethodType.BFS;

    int[] findDFSPath(int from, int to, TileType[] world)
    {
        int max_tiles = n_x * n_z;

        if (from < 0 || from >= max_tiles || to < 0 || to >= max_tiles) return null;

        int[] parents = new int[max_tiles];
        for (int i = 0; i < parents.Length; i++) parents[i] = -1;
        
        bool[] visited = new bool[max_tiles];
        for (int i = 0; i < visited.Length; i++) visited[i] = false;

        List<int> N = new List<int>() { from };
        int nIterations = 0;
        while (N.Count > 0)
        {
            var x_shortest = N.Min(n => Mathf.Abs(to % n_x - n % n_x));
            var z_shortest = N.Min(n => Mathf.Abs(to / n_z - n / n_z));
            var current = N.First(n => Mathf.Abs(to % n_x - n % n_x) == x_shortest || Mathf.Abs(to / n_z - n / n_z) == z_shortest);
            N.Remove(current);

            if (visited[current] == true) continue;
            visited[current] = true;

            nIterations++;

            int[] neighbors = findNeighbors(current, world);
            foreach (var neighbor in neighbors)
            {

                if (neighbor == to)
                {
                    // found the destination
                    parents[neighbor] = current;
                    print("nIterations: " + nIterations);
                    return buildPath(parents, from, to); // read parents array and construct the shoretest path by traversal
                }

                if (parents[neighbor] == -1) // neighbor's parent is not set yet.
                {
                    parents[neighbor] = current; // make current tile as neighbor's parent
                    N.Add(neighbor); // push
                }
            }
        }
        return null; // I cannot find any path from source to destination        
    }

    int[] findBFSPath(int from, int to, TileType[] world) {
        int max_tiles = n_x * n_z;

        if (from < 0 || from >= max_tiles || to < 0 || to >= max_tiles) return null;

        int[] parents = new int[max_tiles];
        for (int i = 0; i < parents.Length; i++) parents[i] = -1;

        List<int> N = new List<int>() { from };
        int nIterations = 0;
        while (N.Count > 0) {
            int current = N[0]; N.RemoveAt(0); // dequeue
            nIterations++;

            int[] neighbors = findNeighbors(current, world);
            foreach (var neighbor in neighbors) {
                if (neighbor == to) {
                    // found the destination
                    parents[neighbor] = current;
                    return buildPath(parents, from, to); // read parents array and construct the shoretest path by traversal
                }

                if (parents[neighbor] == -1) // neighbor's parent is not set yet.
                {
                    parents[neighbor] = current; // make current tile as neighbor's parent
                    N.Add(neighbor); // enqueue
                }
            }
        }

        return null;
    }
    

    int[] findAstarPath(int from, int to, TileType[] world)
    {
        int max_tiles = n_x * n_z;

        if (from < 0 || from >= max_tiles || to < 0 || to >= max_tiles) return null;

        // initialize the parents of all tiles to negative value, implying no tile number associated.
        int[] parents = new int[max_tiles];       

        for (int i = 0; i < parents.Length; i++) parents[i] = -1;

        List<Node> closed = new List<Node>();
        List<Node> open = new List<Node>() { new Node { no = from, f = 0f, g = 0f}  };
        int nIterations = 0;
        while (open.Count > 0) 
        {
            var lowScore = open.Min(node => node.f);
            var current = open.First(n => n.f == lowScore);
            open.Remove(current);
            closed.Add(current);
            int[] neighbors = findNeighbors(current.no, world);            
            nIterations++;
            foreach (var neighbor in neighbors)
            {
                if (neighbor == to) 
                { 
                    // found the destination
                    parents[neighbor] = current.no;
                    print("nIterations: " + nIterations);
                    return buildPath(parents, from, to); // read parents array and construct the shoretest path by traversal
                }

                if (closed.FirstOrDefault(n => n.no == neighbor) != null) continue;

                // computeDistance(current.no, neighbor) : global cost 계산시 인접 노드간 거리를 고려. 사선인 경우, sqrt(2)가 반환
                var g = current.g + computeDistance(current.no, neighbor);
                var h = computeDistance(neighbor, to); // computeDistance(neighbor, to) : heuristic cost 계산
                var nodeInOpen = open.FirstOrDefault(n => n.no == neighbor);
                if (nodeInOpen == null)
                {
                    parents[neighbor] = current.no;
                    
                    open.Insert(0, new Node { no = neighbor, f = g + h, g = g });
                    continue;
                }
                if ( g + h < nodeInOpen.f)
                {
                    nodeInOpen.f = g + h;
                    nodeInOpen.g = g;
                    parents[neighbor] = current.no;
                }
            }
        }
        return null; // I cannot find any path from source to destination        
    }

    public List<Vector3> GetPathVector3(Vector3 destination) {
        int start = pos2Cell(player.position);
        int end = pos2Cell(destination);
        int[] path = null;

        if (method == MethodType.DFS)
            path = findDFSPath(start, end, world);
        else if (method == MethodType.BFS)
            path = findBFSPath(start, end, world);
        else if (method == MethodType.AStar)
            path = findAstarPath(start, end, world);
        if (path == null) return default;

        // path should start from "source" to "destination".

        drawPath(path);

        List<int> remaining = new List<int>(path); // convert int array to List
        List<Vector3> pathVec3 = new List<Vector3>();
        remaining.RemoveAt(0); // we don't need the first one, since the first element should be same as that of source.
        while (remaining.Count > 0) {
            int to = remaining[0]; remaining.RemoveAt(0);

            Vector3 toLoc = locateToCenter(cell2Pos(to));
            toLoc.y = 0.5f;
            pathVec3.Add(toLoc);
        }

        return pathVec3;
    }
}

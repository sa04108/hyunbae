#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

using namespace std;

struct graph_info
{
	int node;
	int alpha, beta;
	int leaf_node_counter;
	bool is_first_player;
};

vector<int> nodes;
vector<vector<graph_info>> graph;

int normal_negamax_counter = 0;

int minimax(int node, bool is_first_player)
{
	if (graph[node].empty())
	{
		return nodes[node];
	}

	if (is_first_player)
	{
		int value = -std::numeric_limits<int>::max();
		for (auto& child : graph[node])
		{
			child.is_first_player = true;
			child.alpha = minimax(child.node, false);
			value = max(value, child.alpha);
		}

		return value;
	}
	else
	{
		int value = std::numeric_limits<int>::max();
		for (auto& child : graph[node])
		{
			child.is_first_player = false;
			child.alpha = minimax(child.node, true);
			value = min(value, child.alpha);
		}

		return value;
	}
}

int negamax(int node, int alpha, int beta)
{
	if (graph[node].empty())
	{
		++normal_negamax_counter;
		return nodes[node];
	}
	else
	{
		for (auto child = graph[node].begin(); child != graph[node].end(); child++)
		{
			int val = -negamax(child->node, -beta, -alpha);
			if (val >= beta)
				return val;
			if (val > alpha)
				alpha = val;
		}

		return alpha;
	}
}

int get_leaf_node(int node)
{
	if (graph[node].empty())
		return 1;

	int result = 0;
	for (auto& child : graph[node])
	{
		child.leaf_node_counter = get_leaf_node(child.node);
		result += child.leaf_node_counter;
	}

	return result;
}

int main()
{
	int n;	cin >> n;

	nodes.assign(n + 1, 0);
	graph.assign(n + 1, { });

	for (int i = 1; i <= n; i++)
	{
		cin >> nodes[i];
	}

	for (int i = 1; i <= n; i++)
	{
		int k;	cin >> k;
		for (int j = 0; j < k; j++)
		{
			int t;	cin >> t;
			graph[i].push_back({ t, 0, 0, 0, true });
		}
	}

	get_leaf_node(1);
	minimax(1, true);

	for (auto& it : graph)
	{
		sort(it.begin(), it.end(), [](const graph_info& left, const graph_info& right)
			{
				if (left.alpha == right.alpha)
					return left.leaf_node_counter < right.leaf_node_counter;

				return left.is_first_player ? left.alpha > right.alpha : left.alpha < right.alpha;
			});
	}

	normal_negamax_counter = 0;
	negamax(1, -std::numeric_limits<int>::max(), std::numeric_limits<int>::max());

	cout << normal_negamax_counter << ' ';

	for (auto& it : graph)
	{
		sort(it.begin(), it.end(), [](const graph_info& left, const graph_info& right)
			{
				if (left.alpha == right.alpha)
					return left.leaf_node_counter > right.leaf_node_counter;

				return left.is_first_player ? left.alpha < right.alpha : left.alpha > right.alpha;
			});
	}

	normal_negamax_counter = 0;
	negamax(1, -std::numeric_limits<int>::max(), std::numeric_limits<int>::max());

	cout << normal_negamax_counter << '\n';

	return 0;
}
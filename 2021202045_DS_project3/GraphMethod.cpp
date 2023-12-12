#include "GraphMethod.h"

bool BFS(Graph* graph, int vertex)  //function BFS
{
	ofstream flog1;
	flog1.open("log.txt", ios::app);  //call ofstream
	bool* visited = new bool[MAX];   
	vector <int> v;     //vector for printing
	fill(visited, visited + MAX, false); //initialize visited
	queue<int> q;
	q.push(vertex);
	visited[vertex] = true;
	flog1 << "======BFS=======" << "\n";
	flog1 << "startvertex : " << vertex << endl;
	while (!q.empty()) {
		map<int, int>* map_ad = new map<int,int>; //map of get adjacent edge
		int x = q.front();
		graph->getAdjacentEdges_UD(x, map_ad);  //x's adjacent edges
		q.pop();
		v.push_back(x);    //store x
		for (auto i = map_ad->begin(); i != map_ad->end(); i++) { // traversal of adjacent edge
		
			int w = i->first;
			if (!visited[w]) {  //if not visited 
				q.push(w);  //push to queue
				visited[w] = true; //change if visited
			}
		}
		map_ad->clear();  //clear map_ad
		delete map_ad;  //delete map_ad
	}
	for (int it=0; it<v.size(); it++)
	{
		flog1 << v[it];       //print
		if(it != v.size()-1)
		flog1 << " -> ";
	}
	flog1 << "\n";
	//delete memory
	delete[] visited; 
	vector<int>().swap(v);
	flog1.close();
	return 1;
}

bool DFS(Graph* graph, int vertex)
{
	ofstream flog1;
	flog1.open("log.txt", ios::app); //call ofstream
	bool* visited = new bool[MAX];
	vector <int> v;
	fill(visited, visited + MAX, false); //initialize visited
	stack <int> st;  //call stack st
	flog1 << "======DFS=======" << "\n";
	flog1 << "startvertex : " << vertex << endl;
	st.push(vertex);  
	visited[vertex] = true;   //change visited
	v.push_back(vertex);
	while (!st.empty()) {
		map<int, int>* map_ad = new map<int, int>;  //map of getting adjacent edge 
		int x = st.top();
		graph->getAdjacentEdges_UD(x, map_ad);  //x's adjacent edge of undirected graph
		st.pop();  //pop
		for (auto i = map_ad->begin(); i != map_ad->end(); i++) {
			int w = i->first;
			if (!visited[w]) {  //if not visited
				st.push(x); 
				st.push(w);
				visited[w] = true; //change visited
				v.push_back(w);  //vector push->to print
				break;
			}
		}
		//delete memory
		map_ad->clear();
		delete map_ad;
	}
	for (int it = 0; it < v.size(); it++)
	{
		flog1 << v[it];  //print
		if (it != v.size() - 1)
			flog1 << " -> ";
	}
	flog1 << "\n";
	//delete memory
	delete[] visited;
	vector<int>().swap(v);
	flog1.close();
	return 1;
}

bool DFS_R(Graph* graph, bool* visit, int vertex,int count, queue<int>* stk)
{
	ofstream flog1;
	flog1.open("log.txt", ios::app);  //call ofstream
	
	map<int, int>* m = new map<int, int>;
	if (visit[vertex])  //if already visit
	{
		return true;
	}
	visit[vertex] = true;  //change visit condition
	stk->push(vertex);
	count++;
	graph->getAdjacentEdges_UD(vertex, m);

	for (auto it_ = m->begin(); it_ != m->end(); it_++)  //traversal vertex's adjacent edge
	{
		int w = it_->first;
		if (!visit[w])   //if not visit
		{
			DFS_R(graph, visit, w,count,stk); //recursive function
		}
	}
	int co =0;
	while (!stk->empty()) {  //print 
		int path = stk->front();
		flog1 << path;
		stk->pop();
		co++;
		if (co != graph->getSize())
		{
			flog1 << " -> ";
		}

	}
	//delete memory
	m->clear();
	delete m;
	flog1.close();
	return 1;
}

bool Kruskal(Graph* graph)
{
	ofstream flog1;
	flog1.open("log.txt", ios::app); //call ofstream
	int size = graph->getSize();
	int sum = 0;
	vector<pair<pair<int, int>, int>> vec; //store weight and node information
	
	for (int i = 0; i < graph->getSize(); i++) {
		map<int, int>* m = new map<int, int>;
		graph->getAdjacentEdges_UD(i, m);          //traversal all nodes' adjacent edge
		for (auto it = m->begin(); it != m->end(); it++)
		{
			
			if (it->second < 0) return 0;             //if there is negative weight
			vec.push_back(pair < pair<int, int>, int>({ i, it->first }, it->second));
			

		}
		m->clear();
		delete m;
	}
	
	int k = 1;
	int* arr = new int[vec.size()+1];  //enough memory allocation
	arr[0] = 0;
	for (auto j = vec.begin(); j != vec.end(); j++) {  //store only weight for sorting
		arr[k] = j->second;
		k++;
	}
	quickSort(arr, 1, vec.size()); //quick sort and insertion sort
	int* parent= new int[size];    //parent array
	for (int p = 0; p < size; p++) {  //initialize parent -> to itself
		parent[p] = p;
	}
	
	cout<<"\n";
	int count = 0;  //value if can make mst
	map<int, int>* mm = new map<int, int>[size];
	int v_size = vec.size();
	
	for (int i_ = 1; i_ <= v_size+1; i_++) {   //traversal of all weights
		for (auto mit = vec.begin(); mit != vec.end(); mit++) { //traversal of all information
			
			if (arr[i_] == mit->second) {  //match weight and node,edge information
				
				pair<int, int>node = mit->first;
				int from = node.first;
				int to = node.second;
			 
				if (Find(parent, from) != Find(parent, to)) {  //if can't make cycle
					Union(parent,from,to); //union
					mm[from].insert(make_pair(to, mit->second));  //store edge in mm
					mm[to].insert({ from, mit->second });
					
					count++;  //count++
					
					sum = sum+ mit->second; //update sum
				}
				vec.erase(mit--);   //if connected edge->delete
			}
		}
	}
	
	if (count != size - 1) {    //can't make mst
		return 0;
	}
	flog1 << "======Kruskal=======" << "\n";     //print kruskal
	for (int i = 0; i < size; i++)
	{
		flog1 << "[" << i << "] ";
		for (auto it = mm[i].begin(); it != mm[i].end(); it++)
		{
			flog1 << it->first << "(" << it->second << ") ";
		}
		flog1 << endl;
	}

	flog1 << "cost:"<<sum << endl;
	
	//delete memory
	delete[] arr;
	delete[] parent;
	vector<pair<pair<int, int>, int>>().swap(vec);
	delete[]mm;
	flog1.close();
	return 1;
}

bool Dijkstra(Graph* graph, int vertex)
{
	ofstream flog1;
	flog1.open("log.txt", ios::app);  //call ofstream
	bool* visited = new bool[graph->getSize()+1];
	fill(visited, visited + graph->getSize()+1, false); //initialize visited
	int* dist = new int[graph->getSize()];
	int** len = new int*[graph->getSize()+1];
	int* prev = new int[graph->getSize()];    //store path
	fill(prev, prev + graph->getSize(), MAX);
	for (int i = 0; i < graph->getSize(); i++) {   //intialize len
		len[i] = new int[graph->getSize()];
	}
	for (int i = 0; i < graph->getSize(); i++)  //intialize len -> MAX
	{
		for (int j = 0; j < graph->getSize(); j++)
		{
			len[i][j] = MAX;
		}
	}
	fill(visited, visited + graph->getSize(), false); 
	for (int i = 0; i < graph->getSize(); i++) {  
		map<int, int>* m = new map<int, int>;
		graph->getAdjacentEdges(i, m);
		int k = 0;
		for (auto it = m->begin(); it != m->end(); it++)
		{
			if (it->second < 0) return 0;      //there is negative weight
			len[i][it->first] = it->second;    //initialize len according to graph information
			
		}
	
		m->clear();
		delete m;
	}

	for (int i = 0; i < graph->getSize(); i++) {
		dist[i] = len[vertex][i];  //initiialize dist
		if (len[vertex][i] != MAX) {   //if len is not MAX
			prev[i] = vertex;      //update path
		}
	}
	
	for (int i = 0; i < graph->getSize() - 2; i++) {
		int min_n = 0;
		int idx = 0;
		min_n = MAX;
		
		for (int st = 0; st < graph->getSize(); st++) { //choose the smallest dist 
			if (dist[st] < min_n ) {
				if (!visited[st]) {  //except already visited
					min_n = dist[st];
					idx = st;
				}
			}
		}
		visited[idx] = true; //change visited condition
		
		for (int w = 0; w < graph->getSize(); w++)
		{
			if (visited[w] == false)
			{
				int past = dist[w];
				dist[w] = min(dist[idx] + len[idx][w], dist[w]); //compare distance
				if (dist[w] < past) {  //if update distance
					if (w != vertex) //except start vertex
					{
						prev[w] = idx; //update prev
					}
				}
			}
		}

	}
	
	flog1 << "======Dijkstra=======" << "\n";
	flog1 << "startvertex : " << vertex << endl;
	stack <int> stk; //stack for printing
	for (int i = 0; i < graph->getSize(); i++)
	{	
		int s = 0;
		s = i;
		if (i == vertex) //except start vertex
		{
			continue;
		}
		flog1 << "[" << i << "] ";
		if (prev[s] == MAX)  //no incomming edge
		{
			flog1 << "x "<<endl;
			continue;
		}
	    while (s != MAX) {  //while parent meet MAX
			stk.push(s); //stack push
			s = prev[s];
		}
		while (!stk.empty()) {
			int path = stk.top(); 
			flog1 << path;
			stk.pop(); //pop
			if (!stk.empty())
			{
				flog1 << "->";
			}
			
		}
		if (dist[i] == MAX)  //if path to i
		{
			flog1 << "x ";
		}
		else
		{
			flog1 << "("<<dist[i]<<")" << "\n";
		}
	}
	//delete memory
	delete[]dist;
	delete[]prev;
	delete[]visited;
	for (int i = 0; i < graph->getSize(); i++)
	{
		delete[] len[i];

	}
	delete[] len;
	flog1.close();
	return 1;
}

bool Bellmanford(Graph* graph, int s_vertex, int e_vertex)
{
	ofstream flog1;
	flog1.open("log.txt", ios::app);  //call ofstream
	int size = graph->getSize();
	int* dist = new int[graph->getSize()];
	int** len = new int* [graph->getSize() + 1];
	int* prev = new int[graph->getSize()];
	fill(prev, prev + graph->getSize(), MAX);
	for (int i = 0; i < graph->getSize(); i++) {  //initialize len
		len[i] = new int[graph->getSize()];
	}
	for (int i = 0; i < graph->getSize(); i++)    //initialize all len->MAX
	{
		for (int j = 0; j < graph->getSize(); j++)
		{
			len[i][j] = MAX;
		}
	}
	for (int i = 0; i < graph->getSize(); i++) {
		map<int, int>* m = new map<int, int>;
		graph->getAdjacentEdges(i, m);
		int k = 0;
		for (auto it = m->begin(); it != m->end(); it++) //initialize len according to graph information
		{
			len[i][it->first] = it->second;

		}

		m->clear();
		delete m;
	}
	for (int i = 0; i < size; i++) { //if k==1, edge is 1
		dist[i] = len[s_vertex][i];   //initialize distance
		if (i == s_vertex) {  //if i == start vertex
			len[s_vertex][i] = 0; //initialize 0
			dist[i] = 0;
		}
		if (len[s_vertex][i] != MAX) {
			prev[i] = s_vertex;   //update prev(path)
		}
	}
	for (int k = 2; k <= size - 1; k++) { //k is number of pathes
		for (int j = 0; j < size; j++) {  //j is end vertex
			if (j != s_vertex) {
				for (int l = 0; l < size; l++) {
					if (len[l][j] != MAX) {   //if len[l][j] is not MAX
						if (dist[l] == MAX || len[l][j] == MAX) { //if path is Max
							continue;
						}
						int past = dist[j];
						dist[j] = min(dist[j], dist[l] + len[l][j]); //compare
						if (dist[j] < past) { //update prev
							prev[j] = l;
						}
					}
				}
			}
		}
	}
	for (int k = 2; k <= size - 1; k++) {   //if update dist-> generate negative cycle
		for (int j = 0; j < size; j++) {
			if (j != s_vertex) {
				for (int l = 0; l < size; l++) {
					if (len[l][j] != MAX) {
						
						int past = dist[j];
						dist[j] = min(dist[j], dist[l] + len[l][j]);
						
						if (dist[j] < past) {
							
							return 0;
						}
					}
				}
			}
		}
	}

	flog1 << "======Bellman-Ford=======" << "\n";   //same command with printing dijstra but there is start vertex and end vertex in this case
	stack <int> stk;
	
		int s = e_vertex;
		if (s == s_vertex)
		{
			flog1 << e_vertex;
			flog1 << "cost: " << 0 << "\n";
			return 1;
		}

		if (prev[s] == MAX)  //no incomming edge to s
		{
			flog1 << "x\n";
			return 1;
		}
		while (prev[s] != s_vertex) {   //meet start vertex -> out
			
			stk.push(s);
			s = prev[s];
		}
		stk.push(s);
		stk.push(s_vertex);
		while (!stk.empty()) {   //print stack information
			int path = stk.top();
			flog1 << path;
			stk.pop();
			if (!stk.empty())
			{
				flog1 << "->";
			}

		}
		if (dist[e_vertex] == MAX)  //if can't go to end case
		{
			flog1 << "x ";
		}
		else
		{
			flog1 << "\n";
			flog1 << "cost :";
			flog1 <<  dist[e_vertex] << "\n";
		}

	flog1.close();
	//delete memory
	delete[]dist;
	delete[]prev;
	for (int i = 0; i < graph->getSize(); i++)
	{
		delete[] len[i];

	}
	delete[] len;
	return 1;
}

bool FLOYD(Graph* graph)
{
	ofstream flog1;
	flog1.open("log.txt", ios::app); //call ofstream
	int size = graph->getSize();
	int** len = new int* [graph->getSize() + 1];
	
	for (int i = 0; i < graph->getSize(); i++) {
		len[i] = new int[graph->getSize()];
	}
	for (int i = 0; i < graph->getSize(); i++)   // initialize len to Max but i==j->0
	{
		for (int j = 0; j < graph->getSize(); j++)
		{
			len[i][j] = MAX;
			if (i == j) {
				len[i][j] = 0;
			}
		}
	}
	for (int i = 0; i < graph->getSize(); i++) {
		map<int, int>* m = new map<int, int>;  //store get adjacent edge in map
		graph->getAdjacentEdges(i, m);
		int k = 0;
		for (auto it = m->begin(); it != m->end(); it++)
		{
			len[i][it->first] = it->second;                    //update len according to graph information

		}

		m->clear();
		delete m;
	}
	for (int k = 0; k < size; k++) {  // k is vertex of path node
		for (int i = 0; i < size; i++) {  // i is start vertex
			for (int j = 0; j < size; j++) {  // j is end vertex
				if (len[i][k] + len[k][j] < len[i][j]) {  //distance[i,j] = min(distance[i,j], distance[i,n] + distance[n,j])
					if (len[i][k] == MAX || len[k][j] == MAX) {
						continue;
					}
					len[i][j] = len[i][k] + len[k][j];
				}
			}
		}
	}

	for (int k = 0; k < size; k++) {      //for knowing if there is negative cycle
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				if (len[i][k] + len[k][j] < len[i][j]) {  //if negative cycle is, update -> return 0

					return 0;
				}
			}
		}
	}
	flog1 << "======FLOYD=======" << "\n";
	flog1 << '\t';
	for (int i = 0; i < size; i++)                 //same with matrix graph print
	{
		flog1 << "[" << i << "]" << '\t';
	}
	flog1 << endl;

	for (int i = 0; i < size; i++)
	{
		flog1 << "[" << i << "]";
		for (int j = 0; j < size && flog1 << '\t'; j++)
		{
			if (len[i][j] == MAX) {
				flog1 << "x ";
			}
			else
			flog1 << len[i][j];
		}
		flog1 << endl;
	}
	flog1.close();
	//delete memory
	for (int i = 0; i < graph->getSize(); i++)
	{
		delete[] len[i];

	}
	delete[] len;
	return 1;
}
int Find(int parent[],int vertex) {    //if vertexs are in same set -> return its set's root
	if (parent[vertex] == vertex)return vertex;
	return parent[vertex] = Find(parent, parent[vertex]);
}
void Union(int parent[],int vertex1, int vertex2) { //union two set
	int para_a = Find(parent, vertex1);
	int para_b = Find(parent, vertex2);
	if (para_a < para_b) parent[para_b] = para_a;  //bigger is subtree of smaller root value
	else parent[para_a] = para_b;
	
	return;
};
void insertionSort(int* a, const int n1,const int n2) {
	for (int j = n1+1; j <= n2; j++) {
		int temp = a[j];
		insert(a, temp, j - 1);   // call insert function
	}
}
void insert(int* a, const int& e, int i) {
	a[0] = e;  //store sorting value
	while (e < a[i]) {  
		a[i + 1] = a[i];  //swap
		i--;
	}
	a[i + 1] = e; //if find location of e
}
void quickSort(int* arr, int left, int right) {
	int j = 0;
	int pivot = 0;
	if (left < right)  //if left < right
	{
		if (right - left + 1 < 6)  //if size of array less than 6
		{
			insertionSort(arr,left,right);  //insertion sort
		}
		else
		{
			int i = left;
			j = right + 1;
			pivot = arr[left]; //pivot is most left value
			do
			{
				do i++; while (arr[i] < pivot);
				do j--; while (arr[j] > pivot);
				if (i < j) swap(arr[i], arr[j]); //swap 
			} while (i < j);
			swap(arr[left], arr[j]); //final swap
			quickSort(arr, left, j - 1); //recursive function of left segment
			quickSort(arr, j + 1, right); //recursive function of right segment
		}
	}

	return;
};

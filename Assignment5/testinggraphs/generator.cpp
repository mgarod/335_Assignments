#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
using namespace std;

// EDGEMAX scales each edge value to be within [0, EDGEMAX]
const int EDGEMAX = 100;

int main(int argc, char** argv){
	if(argc != 2)
		cout << "Usage: " << argv[1] << " <number of nodes>" << endl;

	srand(static_cast <unsigned> (time(0)));	

	ofstream ofs("Graph.txt");
	int num = atoi(argv[1]);

	ofs << num << endl;

	for (int i = 0; i < num; ++i){
		ofs << i << " ";

		for (int j=0; j < num; ++j){
			// This condition will disallow loops
			//if(i == j) continue;
			
			// Random nummber r is within [0,1]
			float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);

			// EDGEMAX scales r to be within [0, EDGEMAX]
			r *= EDGEMAX;

			// comment out to toggle float vs integer edge cost
			// r = static_cast<int>(r);
		
			// Edges with less than this value are deleted
			// Set discardlimit 0 to get complete graphs
			// Set discardlimit closer to EDGEMAX for sparse graphs
			int discardlimit = EDGEMAX * 3 / 4;
			if (r < discardlimit) continue;

			ofs << j << " " << r << " ";
		}

		ofs << "-1\n";
	}

	ofs.close();
}
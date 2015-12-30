SIZE="10"
g++ -std=c++11 -Wall generator.cpp &&
./a.out $SIZE;
rm a.out;

g++ -std=c++11 -Wall main.cpp Graph.cpp;
./a.out Graph.txt 0 > output.txt;
echo '\n' >> output.txt;
./a.out Graph.txt 1 >> output.txt;
echo '\n' >> output.txt;
./a.out Graph.txt 2 >> output.txt;
echo '\n' >> output.txt;
./a.out Graph.txt 3 >> output.txt;
echo '\n' >> output.txt;
./a.out Graph.txt 4 >> output.txt;
echo '\n' >> output.txt;
./a.out Graph.txt 5 >> output.txt;
echo '\n' >> output.txt;
./a.out Graph.txt 6 >> output.txt;
echo '\n' >> output.txt;
./a.out Graph.txt 7 >> output.txt;
echo '\n' >> output.txt;
./a.out Graph.txt 8 >> output.txt;
echo '\n' >> output.txt;
./a.out Graph.txt 9 >> output.txt;
rm a.out;
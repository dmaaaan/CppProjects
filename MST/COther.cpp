/*
 * COther.cpp
 *
 *  Created on: 29 cze 2019
 *      Author: Denis
 */

#include "COther.h"


#include <fstream>

#include <cassert> //for asser
#include <climits>	//int_max int_min
#include <cstdio>

#include<iostream>
#include<list>
#include<iterator>


using namespace std;

//forward declaration: class CGraph;

COther::COther():CGraph() {

		int i=0;int DiagPos=0;int j=0;
		currVerDistance=new int[size];
		closestEdge=new int[size];
		mstCheck= new bool[size];
		adj_list= new list<int>[size];

		for(i=0;i<size;i++){									//default values
			mstCheck[i]=false;
			currVerDistance[i]=INT_MAX;
			closestEdge[i]=INT_MIN;
		}

		for(i=0;i<size;i++){									//adjecencyList[vertex].addConnectedVertex(pairof(vertex,value))
			while(j<DiagPos)
			{
				if(i!=j && costGraph[i][j]!=0)					//fill the list
				{
				//	adj_list[i].push_back(j);					//dont use debugger for it- it always crashes
				//	adj_list[j].push_back(i);
				}
				j++;
			}
			DiagPos++;	//every row gets one more column to check (symmetry of array/ optimization)
			j=0;		//SUPER IMPORTANT WHEN NOT USING FOR()
		}
}

COther::~COther() {

}

int COther::minAlg(){

	int min= INT_MAX;
	int minIndex;


	for(int v=0;v<size;v++)
	{
			if(mstCheck[v]==false && currVerDistance[v]<min){	//1. iteration->currVerDistance[0]=0
					min=currVerDistance[v];				//v- vertex to which distance equals currVerDistance[v]
					minIndex=v;
			}
	}

	return minIndex;
}

void COther::calcDistances(){

	for(int i=0; i<size-1;i++){
		int u=minAlg();									//u- vertex closest to the current one except for already added
		mstCheck[u]=true;								//table saving info that vertex u is done
														//THIS IS THE REASON WHY WE SET -1 AND GET RUBBISH
		//below if() never enters for v=begin because at the beginning begin is added to finished group..
		//.. and doesnt have its currVerDistance set
		for(int v=0;v<size;v++)
		{
			if(costGraph[u][v] && mstCheck[v]==false && costGraph[u][v]<currVerDistance[v])
			{											//if graph value is diff from zero, if v vertex is not done yet, if distance to v is really smaller that
				currVerDistance[v]=costGraph[u][v];		//save distance between the closest vertices
				closestEdge[v]=u;						//v- current vertex, u- look above
			}
		}
	}
}

void COther::printMST(){
	ofstream testList;
	testList.open("tList.txt",fstream::app); 		// fstream::app is the open mode "append" meaning
	testList<<"The graph is bidirectional!"<<endl;
	testList<<"[edge]<->[closestToIt](value)"<<endl;
	for(int i = 0; i<size; i++)
	{
		testList<<i<<"<->"<<closestEdge[i]<<"("<<costGraph[i][closestEdge[i]]<<")"<<endl;
	}			//i-current, closest- next to it
	testList.close();
}

void COther::printAdjList() {
	ofstream testList;
	testList.open("tList.txt",fstream::out);
	for(int i = 0; i<size; i++)
	{
		testList << i << "--->";
		list<int> :: iterator it;
		for(it = adj_list[i].begin(); it != adj_list[i].end(); ++it)
		{
			 testList << *it << " ";
		}
		testList << endl;
	}

	testList.close();
}

void COther::enterBegin(){
	int begin;
	cout<<"podaj poczatek.."<<endl;
	cin>>begin;					//pick vertex e.g. 0 and start with it. very importnat
	//begin=3;
	currVerDistance[begin]=0; 	//vertex=begin will be picked by the algorithm as the first because its distance (loop)=0;
	cout<<"podano:"<<begin<<endl;
	closestEdge[begin]=-1;		//closest point to begin is -1. Why? They say there has to be first node created before the algorithm is startex
}								//they call it the root of MST

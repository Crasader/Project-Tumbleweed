#pragma once
#include "cocos2d.h"
#include "SpawnObject.h"
#include "Table.h"
#include "baseObjectManager.h"
#include "Enemy.h"
namespace Sedna {
	class SpawnManager//TODO
	{
	public:
		SpawnManager(cocos2d::Scene* s) :scene(s) {}
		void update(float dt, int DDOS);
		std::vector <Sedna::Table*> tableList;
		std::vector<Sedna::Outlaw*>outlawList;
	private:
		float totalTime = 0.0f;
		cocos2d::Scene* scene;

		Sedna::Table* baseTable;
		Sedna::Outlaw* outlaw;
		Sedna::ShotgunOutlaw* shotgunOutlaw;
		Sedna::RifleOutlaw* rifleOutlaw;



		void tableSpawn(int DDOS);
		void outlawSpawn(int DDOS);
		void shotgunOutlawSpawn(int DDOS);
		void rifleOutlawSpawn(int DDOS);
		

		SpawnObject tables = SpawnObject(5.0f,5,1.0f,true);
		SpawnObject outlaws = SpawnObject(2.0f,6,2.0f);
		SpawnObject outlawChain = SpawnObject(20.0f,10.0f,10.0f,5,true);
		SpawnObject shotgunOutlaws = SpawnObject(7.0f,4.0f,1.0f);
		SpawnObject rifleOutlaws = SpawnObject(14.0f, 7.0f, 1.0f);

	};



}
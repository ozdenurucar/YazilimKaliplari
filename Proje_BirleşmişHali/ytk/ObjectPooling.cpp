#include "ObjectPooling.h"


const bool &ObstacleContext::getisActive() const {
	return is_Active;
}

void ObstacleContext::setisActive(const bool &value) {
	is_Active = value;
}

ObstacleContext::ObstacleContext() {
	is_Active = false;
	std::cout << "ObstacleContext yaratildi" << endl;
}

void ObstacleContext::Open() {
	std::cout << "Obstacle kullanima acildi" << endl;
	//Burada obstacle kullanima acilacak
	//Obstacle ın koordinatları random verilebilir veya kullanicidan alinabilir
}

void ObstacleContext::Close() {
	std::cout << "Obstacle kullanima  kapandi" << endl;
	//Burada obstacle kullanimi bitecek
}

void ObstacleContext::Execute(const string &query) {
	std::cout << query << "Obstacle kullanimda" << endl;
}

//-------------------------------------------------

const string &Obstacle::getObstacleString() const {
	return ObstacleString;
}

void Obstacle::setObstacleString(const string &value) {
	ObstacleString = value;
}

Obstacle::Obstacle(const string &ObstacleString) {
	this->ObstacleString = ObstacleString;
}

void Obstacle::Open() {
	poolManager = PoolManager::createPool();
	con = poolManager->TakeObstacle(this->ObstacleString);

	if (con != nullptr) {
		con->Open();
	}
	else {
		cout << "Havuzda hic uygun nesne yok. Bekle" << endl;
		//Bekleyen obstacle'lar bir listede tutulacak
	}
}

void Obstacle::Close() {
	poolManager->ReleaseObstacle(con);
	con->Close();
	//Bekleyen obstacle listesi kontrol edilecek. Eğer bekleyen varsa onun acilme islemlerine yönlendirme yapilacak
}

void Obstacle::Execute(const string &query) {
	con->Execute(query);
}

//-------------------------------------------------

PoolManager::PoolManager() {
	pools = unordered_map<string, vector<ObstacleContext*>>(POOL_SİZE);
}

PoolManager* PoolManager::pm = nullptr;

PoolManager *PoolManager::createPool() {
	//PoolManager singleton
	if (pm == nullptr) {
		pm = new PoolManager();
	}
	return pm;
}

ObstacleContext *PoolManager::TakeObstacle(const string &key) {
	if (pools.find(key) != pools.end()) {
		vector<ObstacleContext*> objects = static_cast<vector<ObstacleContext*>>(pools[key]);
		for (auto cu : objects) {
			if (!cu->getisActive()) {
				return cu;
			}
		}
	}
	else {
		vector<ObstacleContext*> yeniHavuz = vectorhelper::VectorWithReservedSize<ObstacleContext*>(POOL_SİZE);
		for (int i = 0; i <= POOL_SİZE - 1; i++) {
			yeniHavuz.push_back(new ObstacleContext());
		}
		pools.insert(make_pair(key, yeniHavuz));
		ObstacleContext *cu = yeniHavuz[0];
		cu->setisActive(true);

		return cu;
	}
	return nullptr;
}

void PoolManager::ReleaseObstacle(ObstacleContext *connection) {
	connection->setisActive(false);
}



#include "stdafx.h"
#include <sstream>
#include <iostream>
#include "rrt.h"

int main()
{
	//random sayı üreticileri
	std::random_device rd;
	std::mt19937 gen(rd());
	std::pair<float, float> random_point;
	RTTplanner *prototype = new RTTplanner();
	costmap_2d::Costmap2D* costmap_;
	planner_1.initialize("First Planner", costmap_); // parametre olarak isim ve haritayı alan constructor çağırılır.
	RTTplanner *planner_1 = new RTTplanner(*prototype); //Deep copy (Referansı ile birlikte yapılır nesnenin tüm bilgileri kopyalanır)
	prototype->getObstacleMap();
	//rastgele bir noktaya engel eklenirse
	//problemin aslında engelin sınırlarının da veirlmesi gereklidir ancak basitçe örneklemek için rastgele(x,y) çifti kullanılmıştır.
	//std::uniform_real_distribution<> x(-map_width, map_width);
	//std::uniform_real_distribution<> y(-map_height, map_height);
	//haritanın sınırları verilmesi gerkiyor ancak projenin şu aşamasında henüz harita oluşturulamadıgı icin rastgele sayilar verilmistir
	std::uniform_real_distribution<> x(-10, 10);
	std::uniform_real_distribution<> y(-5, 5);
	random_point.first = x(gen);
	random_point.second = y(gen);
	planner_1->obstacles.push_back(random_point);// random bir koordinat
	RTTplanner *planner_2 = new RTTplanner();
	planner_2 = prototype;// shallow copy 
	planner_2->getObstacleMap;
	prototype->getObstacleMap;
}
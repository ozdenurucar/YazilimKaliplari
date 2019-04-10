#ifndef INCLUDE_TURTLEBOT_RRT_TURTLEBOT_RRT_H_
#define INCLUDE_TURTLEBOT_RRT_TURTLEBOT_RRT_H_

/** ROS kutuphanesi  **/
#include <ros/ros.h>

#include <move_base_msgs/MoveBaseAction.h>
#include <pluginlib/class_list_macros.h>
/** gloabal yol planlayıcı arayüzü için **/
#include <costmap_2d/costmap_2d_ros.h>
#include <costmap_2d/costmap_2d.h>
#include <nav_core/base_global_planner.h>
#include <geometry_msgs/PoseStamped.h>
#include <angles/angles.h>
#include <base_local_planner/world_model.h>
#include <base_local_planner/costmap_model.h>

/** standart kutuphaneler **/
#include <iostream>
#include <cmath>
#include <set>
#include <string>
#include <vector>
#include <utility>
#include <boost/random.hpp>
#include "vertex.h"

namespace turtlebot_rrt 
{
	class RTTplanner : public nav_core::BaseGlobalPlanner // nav_core::BaseGlobalPlanner arayüzünden türemiş bir sınıf
	{
	public:
		RRTPlanner(); // RRTPlanner için Yapıcı fonksiyon

		/*  constructor fonksiyon
		    name: düğüme ilişkilendirilecek isim
			costmap_ros: cost_map ros wrapper ı
		*/
		RRTPlanner(std::string name, costmap_2d::Costmap2DROS* costmap_ros);		
		void initialize(std::string name, costmap_2d::Costmap2DROS* costmap_ros); //*Ros handle ı başlat 
		/*
		   start: balangic konumu
		   goal: hedef
		   plan: yapılan yol planı
		*/
		bool makePlan(const geometry_msgs::PoseStamped& start, const geometry_msgs::PoseStamped& goal,
			std::vector<geometry_msgs::PoseStamped>& plan);
		/*
			engel haritasını döndürür
			std :: vector <bool> Güvenli olmayan hücreler false, güvenli hücreler true
		*/
		std::vector<bool> getObstacleMap(){ return obstacle_map_;}
		/*
			rrt vertex ağacını döndürür
		*/
		std::vector<turtlebot_rrt::Vertex> getVertexTree() 
		{
			return vertex_list_;
		}
		/*
			Harita alanında rastgele bir nokta alır
			x, y çifti döndürür
		*/
		std::pair<float, float> GetRandomPoint();
		int GetClosestVertex(std::pair<float, float> random_point);
		void addVertex(turtlebot_rrt::Vertex new_vertex) {
			vertex_list_.push_back(new_vertex);
		}
		float GetDistance(std::pair<float, float> start_point,
			std::pair<float, float> end_point);
		bool MoveTowardsPoint(int closest_vertex,
			std::pair<float, float> random_point);
		bool ReachedGoal(int new_vertex);
		std::vector<geometry_msgs::PoseStamped>
			BuildPlan(int goal_index,
				const geometry_msgs::PoseStamped& start,
				const geometry_msgs::PoseStamped& goal);
		int FindPath(const geometry_msgs::PoseStamped& start,
			const geometry_msgs::PoseStamped& goal);
		bool IsSafe(std::pair<float, float> start_point,
			std::pair<float, float> end_point);
		std::vector<pair<float, float>> obstacles;
	private:
		ros::NodeHandle node_handle_;
		costmap_2d::Costmap2DROS* costmap_ros_; //Kontrolörün kullanacağı maliyet haritası için ROS wrapper
		costmap_2d::Costmap2D* costmap_;
		int max_iterations_;
		int current_iterations_;
		base_local_planner::WorldModel* world_model_; //Maliyet haritasıyla ilişkili dünya modeli
		bool initialized_;
		float goal_radius_;
		float step_size_;
		float delta_;
		float x_origin_;
		float y_origin_;
		float x_goal_;
		float y_goal_;
		unsigned int map_width_cells_;
		unsigned int map_height_cells_;
		std::vector<turtlebot_rrt::Vertex> vertex_list_;
	};
	void RRTPlanner::initialize(std::string name, costmap_2d::Costmap2DROS* costmap_ros) 
	{
		if (!initialized_) 
		{
			//haritayi baslat
			costmap_ros_ = costmap_ros;
			costmap_ = costmap_ros->getCostmap();

			// ros dugumunu baslat
			ros::NodeHandle node("~/turtlebot_rrt");
			node_handle_ = node;
			world_model_ = new base_local_planner::CostmapModel(*costmap_);
			node_handle_.getParam("/move_base/step_size_", step_size_);
			node_handle_.getParam("/move_base/delta_", delta_);
			node_handle_.getParam("/move_base/goal_radius_", goal_radius_);
			node_handle_.getParam("/move_base/max_iterations_", max_iterations_);
			ROS_INFO("Step size: %.2f, goal radius: %.2f, delta: %.2f, max "
				"iterations: %d", step_size_, goal_radius_, delta_,
				max_iterations_);
			current_iterations_ = 0;

			// costmapdeki engelleri getir
			map_width_cells_ = costmap_->getSizeInCellsX();
			map_height_cells_ = costmap_->getSizeInCellsY();

			for (unsigned int iy = 0; iy < map_height_cells_; iy++) {
				for (unsigned int ix = 0; ix < map_width_cells_; ix++) {
					unsigned char cost = static_cast<int>(costmap_->getCost(ix, iy));
					if (cost >= 115)
						obstacle_map_.push_back(false);
					else
						obstacle_map_.push_back(true);
				}
			}
			// Basladigini goster
			ROS_INFO("RRT planner initialized successfully.");
			initialized_ = true;
		}
		else 
		{
			ROS_WARN("RRT planner has already been initialized.");
		}
	}
	//Prototype pattern icin:
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
}
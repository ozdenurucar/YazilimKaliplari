#ifndef INCLUDE_TURTLEBOT_RRT_TURTLEBOT_RRT_H_
#define INCLUDE_TURTLEBOT_RRT_TURTLEBOT_RRT_H_

/** include ROS libraries **/
#include <ros/ros.h>

#include <move_base_msgs/MoveBaseAction.h>

/** for global path planner interface **/
#include <costmap_2d/costmap_2d_ros.h>
#include <costmap_2d/costmap_2d.h>
#include <nav_core/base_global_planner.h>
#include <geometry_msgs/PoseStamped.h>
#include <angles/angles.h>
#include <base_local_planner/world_model.h>
#include <base_local_planner/costmap_model.h>

/** include standard libraries **/
#include <iostream>
#include <cmath>
#include <set>
#include <string>
#include <vector>
#include <utility>
#include <boost/random.hpp>

/** Local includes **/
#include "vertex.h"

namespace turtlebot_rrt {
	class RRTPlanner : public nav_core::BaseGlobalPlanner 
	{
	public:
		RRTPlanner();
		RRTPlanner(std::string name, costmap_2d::Costmap2DROS* costmap_ros);
		void initialize(std::string name, costmap_2d::Costmap2DROS* costmap_ros);
		bool makePlan(const geometry_msgs::PoseStamped& start, const geometry_msgs::PoseStamped& goal, 
			std::vector<geometry_msgs::PoseStamped>& plan);
		std::vector<bool> getObstacleMap() {
			return obstacle_map_;
		}
		std::vector<turtlebot_rrt::Vertex> getVertexTree() {
			return vertex_list_;
		}
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

	private:
		ros::NodeHandle node_handle_;
		std::vector<bool> obstacle_map_;
		costmap_2d::Costmap2DROS* costmap_ros_;
		costmap_2d::Costmap2D* costmap_;
		int max_iterations_;
		int current_iterations_;
		base_local_planner::WorldModel* world_model_;
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
}  
#endif

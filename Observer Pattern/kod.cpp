#include <vector>
#include <functional>


namespace turtlebot_rrt 
{
class RRTPlanner : public nav_core::BaseGlobalPlanner {
 public:
     RRTPlanner();
     RRTPlanner(std::string name, costmap_2d::Costmap2DROS* costmap_ros);
     void initialize(std::string name,
                     costmap_2d::Costmap2DROS* costmap_ros);
     bool makePlan(const geometry_msgs::PoseStamped& start,
                   const geometry_msgs::PoseStamped& goal,
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

class RRTPlanner : rrtplanner_observer
{
  public:
    virtual bool ReachedGoal(int new_vertex) = 0;
};

class observer_concrete : public rrtplanner_observer
{
  public:
    virtual void notify() override
    { 
     ROS_DEBUG("In ReachedGoal, vertex index: %d.", new_vertex);
    }
};



class map_subject
{
  public:
    void register_observer(rrtplanner_observer& o)
    {
      observers.push_back(o);
    }
    void notify_observers()
    {
      for (rrtplanner_observer& o : observers)
      {
        o.ReachedGoal();
      }
    }
  private:
    std::vector<std::reference_wrapper<rrtplanner_observer>> observers;
};

} 




#pragma once
#ifndef INCLUDE_TURTLEBOT_RRT_VERTEX_H_
#define INCLUDE_TURTLEBOT_RRT_VERTEX_H_

#include <cmath>
#include <utility>

namespace turtlebot_rrt {
	class Vertex {
	private:

		float x_;
		float y_;
		int index_;
		int parent_index_;

	public:
		Vertex() {}
		Vertex(float x, float y, int index, int parent_index);
		~Vertex() {}
		void set_location(float x, float y);
		void set_index(int index);
		void set_parent(int index);
		std::pair<float, float> get_location();
		int get_index();
		int get_parent();
		bool operator==(const Vertex& v) {
			return (x_ == v.x_ && y_ == v.y_ && parent_index_ == v.parent_index_);
		}
		bool operator!=(const Vertex& v) {
			return (x_ != v.x_ || y_ != v.y_ || parent_index_ != v.parent_index_);
		}
	};
}  // namespace turtlebot_rrt

#endif  // INCLUDE_TURTLEBOT_RRT_VERTEX_H_
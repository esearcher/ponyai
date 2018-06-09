// Copyright @2018 Pony AI Inc. All rights reserved.

#pragma once

#include "homework6/simulation/vehicle_agent.h"

#include "common/proto/agent_status.pb.h"
#include "common/proto/geometry.pb.h"
#include "common/proto/vehicle_status.pb.h"
#include "common/utils/math/math_utils.h"
#include "homework6/simulation/vehicle_agent_factory.h"
#include "homework6/route/find_route.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<iostream>
#include<time.h>
#include<math.h>
#include<algorithm>
#include<vector>

namespace table {

class TableVehicleAgent : public simulation::VehicleAgent {
 public:
  explicit TableVehicleAgent(const std::string& name) : VehicleAgent(name) {}

  virtual void Initialize(const interface::agent::AgentStatus& agent_status) {
    first_run = true;
	acceleration = true;
	control = delta_control = 0.1;
  }

  //generate table
  virtual interface::control::ControlCommand RunOneIteration(
      const interface::agent::AgentStatus& agent_status) {
	
    const double max_velocity = 10, eps = 1e-5;
    interface::control::ControlCommand command;
    //double dist = CalcDistance(agent_status.vehicle_status().position(), agent_status.route_status().destination());
	
	if (first_run){
		FILE *f = fopen((pony_root+"homework6/table.txt").c_str(), "w");
		fclose(f);
	}
	else {
		FILE *f = fopen((pony_root+"homework6/table.txt").c_str(), "a");
		fprintf(f, "%.6lf %.6lf %.6lf\n",len(prev_status.vehicle_status().velocity()), prev_control, len(agent_status.vehicle_status().acceleration_vcs()));
		fclose(f);
	}
	prev_status = agent_status;
	
	first_run = false;
	if (control > 1.0+eps)exit(0);
	if (acceleration){
		command.set_throttle_ratio(control);
		prev_control = control;
		if (len(agent_status.vehicle_status().velocity())>=max_velocity)acceleration = false;
	}
	else {
		command.set_brake_ratio(control);
		prev_control = -control;
		if (len(agent_status.vehicle_status().velocity())<=0.1){
			control += delta_control;
			acceleration = true;
		}
	}
	
    return command;
  }

 private:
  double CalcDistance(const interface::geometry::Vector3d& position,
                      const interface::geometry::Point3D& destination) {
    double sqr_sum =
        math::Sqr(position.x() - destination.x()) + math::Sqr(position.y() - destination.y());
    ;
    return std::sqrt(sqr_sum);
  }

  double len(const interface::geometry::Vector3d& v) {  //x, y
    return std::sqrt(math::Sqr(v.x()) + math::Sqr(v.y()));
  }
  bool first_run, acceleration;
  interface::agent::AgentStatus prev_status;
  double prev_control, control, delta_control;
  interface::route::Route route;
};

}


#ifndef CASCADE_DS_CONTROLLER_H
#define CASCADE_DS_CONTROLLER_H

#include "passive_ds_typedefs.h"
#include <functional>

class CascadeDSController
{
    static const int N_BURN=1000;
    // pointer to dynamics function
    std::function<Vec(Vec)> task_dynamics_;
    //Vec (*task_dynamics_)(Vec);
    // pointer to filter function
    //Vec (*process_filter_)(Vec);
    std::function<Vec(Vec)> process_filter_;
    // impedance parameters
    Mat stiffness_;
    Mat damping_;

    size_t dim_;

    Vec act_pos_;
    Vec filt_pos_;
    Vec ref_pos_;
    Vec ref_vel_;



public:
    CascadeDSController(size_t dim, std::function<Vec(Vec)> task_dynamics,std::function<Vec(Vec)> process_filter);
    void ForwardIntegration(realtype driving_force, realtype dt,realtype speed_threshold);
    void Reset(const Vec& act_pos);
    Mat IntegrateTrajectory(realtype dt,realtype speed_threshold,realtype t_max);

    void Update(const Vec &act_pos);
    const Vec& ref_pos(){return ref_pos_;}
    size_t dim(){return dim_;}
};

#endif // CASCADE_DS_CONTROLLER_H
#ifndef SRC_U_DERIVATIVE_H_
#define SRC_U_DERIVATIVE_H_

#include "util.h"
#include "data.h"
#include "cell.h"
#include "grid.h"
#include "minmod.h"
#include "data_struct.h"
#include <string.h>
#include <iostream>

class U_derivative {
 private:
     const InitData &DATA;
     const EOS &eos;
     Minmod minmod;
     dUsupMat dUsup;
     Mat4x4 dUoverTsup; 
 public:
    U_derivative(const InitData &DATA_in, const EOS &eosIn);
    void MakedU(const double tau, SCGrid &arena_prev, SCGrid &arena_current,
                const int ix, const int iy, const int ieta);

    //! this function returns the expansion rate on the grid
    double calculate_expansion_rate(double tau, SCGrid &arena,
                                    int ieta, int ix, int iy);

    //! this function returns Du^\mu
    void calculate_Du_supmu(const double tau, SCGrid &arena, const int ieta,
                            const int ix, const int iy, DumuVec &a);

    //! this function returns the vector D^\mu(\mu_B/T)
    void get_DmuMuBoverTVec(DmuMuBoverTVec &vec);

    //! this function computes the kinetic vorticity
    void calculate_kinetic_vorticity(const double tau, SCGrid &arena,
        const int ieta, const int ix, const int iy, const DumuVec &a_local,
        VorticityVec &omega);

    //! this function computes the thermal vorticity
    void calculate_thermal_vorticity(const double tau, SCGrid &arena,
        const int ieta, const int ix, const int iy, VorticityVec &omega);

    //! This funciton returns the velocity shear tensor sigma^\mu\nu
    void calculate_velocity_shear_tensor(
        const double tau, SCGrid &arena, const int ieta, const int ix,
        const int iy, const DumuVec &a_local, VelocityShearVec &sigma);

    int MakeDSpatial(const double tau, SCGrid &arena, const int ix,
                     const int iy, const int ieta);
    int MakeDTau(const double tau, const Cell_small *grid_pt_prev,
                 const Cell_small *grid_pt);
};

#endif

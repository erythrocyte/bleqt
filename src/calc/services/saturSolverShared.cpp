#include "saturSolverShared.hpp"

#include "mesh/models/faceType.hpp"

namespace ble::src::calc::services::satur_solver_shared {

double get_face_cf(const std::shared_ptr<common::models::SolverData> data,
    const std::shared_ptr<mesh::models::Face> fc)
{
    if (mesh::models::FaceType::is_top_bot(fc->type)) {
        if (data->isFractShoreImperm())
            return 1.0;

        if (data->use_q)
            return 1.0;

        return 1.0 / (2.0 * data->m);
    }

    return 1.0;
}

}
#include "tensorflow/cc/client/client_session.h"
#include "tensorflow/cc/ops/standard_ops.h"
#include "tensorflow/c/c_api_experimental.h"

using namespace tensorflow;
using namespace tensorflow::ops;
using namespace std;

int main()
{
    TF_Status* status = TF_NewStatus();
    string xpu_lib_path = "/home/fengding/github/tmp/intel-extension-for-tensorflow/bazel-bin/itex/libitex_gpu.so";
    TF_LoadPluggableDeviceLibrary(xpu_lib_path.c_str(), status);
    string status_msg(TF_Message(status));
    LOG(INFO) << "#### status " << status_msg;

    auto root = Scope::NewRootScope();
    auto x = Variable(root, {5, 2}, DataType::DT_FLOAT);
    auto assign_x = Assign(root, x, RandomNormal(root, {5, 2}, DataType::DT_FLOAT));
    auto y = Variable(root, {2, 3}, DataType::DT_FLOAT);
    auto assign_y = Assign(root, y, RandomNormal(root, {2, 3}, DataType::DT_FLOAT));
    auto xy = MatMul(root, x, y);
    auto z = Const(root, 2.f, {5, 3});
    auto xyz = Add(root, xy, z);
    auto p_session = new ClientSession(root);
    p_session->Run({assign_x, assign_y}, nullptr);
    vector<Tensor> outputs;
    p_session->Run({x, y, z, xy, xyz}, &outputs);
    LOG(INFO) << "x = " << std::endl << outputs[0].matrix<float>();
    LOG(INFO) << "y = " << std::endl << outputs[1].matrix<float>();
    LOG(INFO) << "xy = " << std::endl << outputs[3].matrix<float>();
    LOG(INFO) << "z = " << std::endl << outputs[2].matrix<float>();
    LOG(INFO) << "xy+z = " << std::endl << outputs[4].matrix<float>();
    delete p_session;
    return 0;
}

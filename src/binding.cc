#include <nan.h>
#include "tensorflow/c/c_api.h"
#include "src/buffer.h"
#include "src/dtype.h"
#include "src/graph.h"
#include "src/library.h"
#include "src/operation.h"
#include "src/session.h"
#include "src/tensor.h"

using namespace v8;

void GetAllOpList(const Nan::FunctionCallbackInfo<Value>& info) {
  TF_Buffer* list = TF_GetAllOpList();
  info.GetReturnValue().Set(
  Nan::CopyBuffer((char *)list->data, list->length).ToLocalChecked());
}

void InitModule(Handle<Object> target) {
  // set modules
  TensorflowNode::DType::Init(target);
  TensorflowNode::Buffer::Init(target);
  TensorflowNode::Tensor::Init(target);
  TensorflowNode::Graph::Init(target);
  TensorflowNode::Operation::Init(target);
  TensorflowNode::Session::Init(target);
  TensorflowNode::Library::Init(target);

  // set version string
  Nan::Set(target,
    Nan::New<String>("version").ToLocalChecked(), 
    Nan::New<String>(TF_Version()).ToLocalChecked());
  target->Set(Nan::New("GetAllOpList").ToLocalChecked(),
               Nan::New<v8::FunctionTemplate>(GetAllOpList)->GetFunction());    
}

NODE_MODULE(tensorflow, InitModule);
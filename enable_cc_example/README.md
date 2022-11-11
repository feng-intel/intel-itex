# How to enable tensorflow C/C++ client for ITEX

## 1. Intall tensorflow 2.10 

   > $ pip install --upgrade pip   
   > $ pip install tensorflow   
   > $ python -c "import tensorflow as tf;print(tf.__version__)"   
   >  2.10  

## 2. Build libtensorflow_cc.so

   > $ git clone https://github.com/tensorflow/tensorflow.git  
   > $ git checkout origin/r2.10 -b r2.10  
   > $ cd tensorflow  
   > Modify as the below, because **TF_LoadPluggableDeviceLibrary** is defined in "//tensorflow/c:c_api_experimental"

```
diff --git a/tensorflow/BUILD b/tensorflow/BUILD
index 19ee8000206..77d8c714729 100644
--- a/tensorflow/BUILD
+++ b/tensorflow/BUILD
@@ -1187,6 +1187,7 @@ tf_cc_shared_library(
     visibility = ["//visibility:public"],
     win_def_file = ":tensorflow_filtered_def_file",
     deps = [
+        "//tensorflow/c:c_api_experimental",
         "//tensorflow/c:c_api",
         "//tensorflow/c:env",
         "//tensorflow/c:kernels",
```

  Call stack: [TF_LoadPluggableDeviceLibrary](https://github.com/tensorflow/tensorflow/blob/master/tensorflow/c/c_api_experimental.cc#L747) -> RegisterPluggableDevicePlugin -> [RegisterPluggableDevicePlugin](https://github.com/tensorflow/tensorflow/blob/master/tensorflow/core/common_runtime/pluggable_device/pluggable_device_plugin_init.cc#L124)

   > $ ./configure  
   > $ bazel build --jobs 96 --config=opt //tensorflow:libtensorflow_cc.so --verbose_failures --experimental_ui_max_stdouterr_bytes=-1  
   > $ ls /home/fengding/github/tensorflow/bazel-bin/tensorflow/libtensorflow_cc.so

## 3. Build itex

   > $ git clone https://github.com/intel/intel-extension-for-tensorflow.git   
   > $ cd intel-extension-for-tensorflow  

```
$ git diff
diff --git a/itex/BUILD b/itex/BUILD
index 547ec668..ac68dadf 100644
--- a/itex/BUILD
+++ b/itex/BUILD
@@ -14,7 +14,6 @@ itex_xpu_binary(
         ],
         "//conditions:default": [],
     }) + [
-        "@local_config_tf//:_pywrap_tensorflow_internal",
         "//itex/core:protos_all_cc",
         "//itex/core/kernels:libitex_common",
     ],
```

  Refer to [itex source build](https://github.com/intel/intel-extension-for-tensorflow/blob/main/docs/install/how_to_build.md) to build libitex_gpu.so, but *NOT* "pip install"  

   > $ ./configure  
   > $ bazel build -c opt --config=gpu  //itex/tools/pip_package:build_pip_package  
   > $ ls bazel-bin/itex/libitex_gpu.so  

## 4. Examples

  Modify xpu_lib_path in  [3_mm_xpu.cpp](./3_mm_xpu.cpp) to your libitex_gpu.so path.  
  Modify **TF_INCLUDE_PATH** and **TFCC_PATH** in [Makefile](./Makefile) to your path.  
  > $ make  
  > $ ./tfcc_test 

target = tfcc_test
cc = g++ -std=c++17

TF_INCLUDE_PATH = /home/fengding/anaconda3/envs/tf2.10_py39/lib/python3.9/site-packages/tensorflow/include
TFCC_PATH = /home/fengding/github/tensorflow/bazel-bin/tensorflow

include = -I $(TF_INCLUDE_PATH)
lib = -L $(TFCC_PATH) -ltensorflow_framework -ltensorflow_cc
flag = -Wl,-rpath=$(TFCC_PATH)
#source = ./0_session.cpp
#source = ./1_const.cpp
#source = ./2_variable.cpp
#source = ./3_mm.cpp
source = ./3_mm_xpu.cpp

$(target): $(source)
	$(cc) $(source) -o $(target) $(include) $(lib) $(flag)

clean:
	rm $(target)

run:
	./$(target)

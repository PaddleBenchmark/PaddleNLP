model_item=gpt3_moe
dp_degree=8
bs_item=8
fp_item=fp32
run_mode=DP_MoE_C8
device_num=N1C8

model=gpt

# get data
cd ./tests
bash ./test_tipc/dygraph/moe/${model}/benchmark_common/prepare.sh
# run
bash ./test_tipc/dygraph/moe/${model}/benchmark_common/run_benchmark.sh ${model_item} ${fp_item} ${dp_degree} ${bs_item} ${run_mode} ${device_num} 2>&1;

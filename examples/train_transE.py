import config
from models import *
import json
import os 
os.environ['CUDA_VISIBLE_DEVICES']='7'
con = config.Config()
con.set_in_path("./benchmarks/FB15K237/")
con.set_work_threads(8)
con.set_train_times(1000)
con.set_nbatches(2125)	
con.set_alpha(5e-5)
con.set_bern(0)
con.set_dimension(1000)
con.set_margin(1.0)
con.set_self_adv(True)
con.set_self_adv_temperature(1.0)
con.set_ent_neg_rate(256)
con.set_rel_neg_rate(0)
con.set_opt_method("Adam")
con.set_save_steps(10)
con.set_valid_steps(10)
con.set_early_stopping_patience(10)
con.set_checkpoint_dir("./checkpoint/FB15K237/transE")
con.set_result_dir("./result/FB15K237/transE")
con.set_test_link(True)
con.set_test_triple(True)
con.init()
con.set_train_model(TransE)
con.train()

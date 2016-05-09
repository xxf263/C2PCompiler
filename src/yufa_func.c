 /*************************************************************************
    > File Name: yufa_func.c
    > Author: xiaofeng
    > Mail: xxf263@gmail.com 
    > Created Time: Thursday, May 05, 2016 AM09:49:09 CST
 ************************************************************************/

#include"compiler.h"

// 为LR1编写的closure函数
int closure_func(PROJECT_SET* p_set){
	int i, j, k;
	PROJECT new_proj;
	PROJECT this_proj;
	int thisOp[OP_LEN];
	int singleOp[OP_LEN];						// 当前待分析的单个的Op，不含-1分割符
	int singleTail[OP_LEN];						// 对应的tail[]
	int index;									// 调用First()函数要用的指标
	int fiSet[OP_LEN];							// First集

	PROJECT_SET* p_set_new = (PROJECT_SET *)malloc(sizeof(PROJECT_SET));
	*p_set_new = *p_set; 						// p_set 赋值

	// 对p_set中每个项目求闭包
	for(i=0; i<p_set->len; i++){
		this_proj = p_set->proj[i];
		thisOp = genOp[this_proj.thisOp[this_proj.pos]];			// thisOp指向B->n形式的所有产生式
		for(j=0; j<OP_LEN && thisOp[j]!=0; j++){
			k = 0;
			index = 0;
			memset(singleOp, 0, OP_LEN*sizeof(int));
			memset(singleTail, 0, TAIL_LEN*sizeof(int));

			if(thisOp[j] == -1){
				// 构建一个新的项目new_proj;
				// 获取singleOp[]
				singleOp[k++] = thisOp[0];		// 获取的singleOp无需-1分割
				for(j=j+1; thisOp[j]!=-1 && thisOp[j]!=0; j++)
					singleOp[k++] = thisOp[j];
				memcpy(new_proj.thisOp, singleOp, sizeof(singleOp));
				// 获取singleTail[]
				if(this_proj.thisOp[this_proj.pos+1]==0){
					memcpy(singleTail, this_proj.tail, sizeof(this_proj.tail));
				}else{
					int flag = 0;
					int h, g=0;
					First(this_proj.thisOp[this_proj.pos+1], &index, fiSet);
					for(h=0; h<OP_LEN && fiSet[h]!=0; h++){
						if(fiSet[h] == E_NUM){
							flag = 1;
							continue;						// 所以此处用了continue
						}
						singleTail[g++] = fiSet[h];
					}
					if(flag == 1)
						memcpy(singleTail+g, this_proj.tail, sizeof(this_proj.tail));
					// print singleTail!! to check!!!
					memset(fiSet, 0, OP_LEN*sizeof(int));
				}
				memcpy(new_proj.tail, singleTail, sizeof(singleTail));
				// 获取pos
				new_proj.pos = 1;

				// 添加项目
				if(!proj_include(p_set, &new_proj)){
					projset_add(p_set_new, &new_proj);
					p_set_new->len++;
				}

				j--;							// 抵消两个j++的效果

			}
		}
	}

	// 是否将项目集加入项目集规范族？
	for(i=0; i<PS_CUR_NUM; i++){
		if(projset_equal(&PS[i], p_set_new))
			return i;
	}

	PS_CUR_NUM++;								// 当前项目集个数加一
	PS[i] = *p_set_new;
	PS[i].index = i;
	return i;
}

void go_func(int ps_index, int m){
	
}

// 判断两个项目是否相等
int proj_equal(PROJECT* proj1, PROJECT* proj2){
	int i;
	if(proj2->pos != proj1->pos)
		return 0;

	for(i=0; i<TAIL_LEN && proj2->tail[i]!=0 && proj1->tail[i]!=0; i++){
		if(proj1->tail[i] != proj2->tail[i])
			return 0;
	}


	for(i=0; i<OP_LEN && proj2->thisOp[i]!=0 && proj1->thisOp[i]!=0; i++){
		if(proj1->thisOp[i] != proj2->thisOp[i])
			return 0;
	}

	return 1;
}

// 判断项目是否包含在项目集里面
int proj_include(PROJECT_SET* p_set, PROJECT* p){
	int i;
	for(i=0; i<p_set->len; i++){
		if(proj_equal(&(p_set->proj[i]), p))
			return 1;
	}
	return 0;
}


// 将项目插入项目集
void projset_add(PROJECT_SET* p_set, PROJECT* p){
	int i;

	p_set->proj[len].pos = p->pos;
	for(i=0; i<OP_LEN && p->thisOp[i]!=0; i++){
		p_set->proj[len].thisOp[i] = p->thisOp[i];
	}
	for(i=0; i<TAIL_LEN && p->tail[i]!=0; i++){
		p_set->proj[len].tail[i] = p->tail[i];
	}
}

// 项目集相等的判断
int projset_equal(PROJECT_SET* p_set1, PROJECT_SET* p_set2){
	int i;
	if(p_set1->len != p_set2->len)
		return 0;
	for(i=0; i<p_set1->len; i++){
		if(!proj_equal(&(p_set1->proj[i]), &(p_set2->proj[i])))
			return 0;
	}

	return 1;
}
#pragma once
/*
 * Copyright (c) 2016-20017 Max Cong <savagecm@qq.com>
 * this code can be found at https://github.com/maxcong001/logger
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#pragma once

//将三位二进制数转为一位十进制数
#include <stdio.h>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <random>
#include <map>
#include <stdlib.h>
#include <time.h>

#include "logger/logger.hpp"
#include "train/trainData.hpp"
using namespace std;

#define innode 2                //输入结点数
#define hidenode 300            //隐含结点数
#define outnode 1               //输出结点数
#define trainsample (2 * 255) //BP训练样本数

class BpNet
{
public:
  void train(double p[trainsample][innode], double t[trainsample][outnode]); //Bp训练
  double p[trainsample][innode];                                             //输入的样本
  double t[trainsample][outnode];                                            //样本要输出的

  double *recognize(double *p); //Bp识别

  void writetrain(); //写训练完的权值
  void readtrain();  //读训练好的权值，这使的不用每次去训练了，只要把训练最好的权值存下来就OK

  BpNet();
  virtual ~BpNet();

public:
  void init();
  double w[innode][hidenode];   //隐含结点权值
  double w1[hidenode][outnode]; //输出结点权值
  double b1[hidenode];          //隐含结点阀值
  double b2[outnode];           //输出结点阀值

  double rate_w;  //权值学习率（输入层-隐含层)
  double rate_w1; //权值学习率 (隐含层-输出层)
  double rate_b1; //隐含层阀值学习率
  double rate_b2; //输出层阀值学习率

  double e;               //误差计算
  double error;           //允许的最大误差
  double result[outnode]; // Bp输出

private:
};

class encode_decode
{
public:
  bool init();
  std::string encode(std::string input);
  std::string decode(std::string input);

public:
  BpNet bpnn;
  std::map<std::string, std::string> dict;
  int input_len;
  std::random_device rd;
  double p[255 * 255][innode];
  double t[255 * 255][outnode];
};

bool encode_decode::init()
{

  input_len = 2;
  // gen train data
  for (unsigned char i = 0; i < 255; i++)
  {
    for (unsigned char j = 0; j < 255; ++j)
    {

#if 0
      std::string tmp((char *)(&i));
      std::string tmp1((char *)(&j));
      tmp = tmp + tmp1;


      std::string tmp_val((char *)(&tmp_char));
      __LOG(debug, " in the map, key is : " << tmp << " . value is : " << tmp_val);
      dict.emplace(tmp, tmp_val);
#endif
      p[i * 255 + j][0] = i/255.0;
      p[i * 255 + j][1] = j/255.0;
      //unsigned char tmp_char = (rd() / (rd.max() - rd.min())) * 256;
      //srand((unsigned)time(NULL));
      double tmp_char = double(j / 255.0);
      //double tmp_char = 0.001;


      t[i * 255 + j][0] = tmp_char;
      //printf(" i is %d, j is %d, tmp_char is %d\n", i, j, tmp_char);
      __LOG(debug, "i is : " << i << ". j is : " << j << ". t,p_char is : " << double(tmp_char));
    }
  }

  __LOG(debug, "generate train data done!");
  bpnn.init();
  int times = 0;
  while (bpnn.error > 0.00007)
  {
    bpnn.e = 0.0;
    times++;
    bpnn.train(p, t);
    cout << "Times=" << times << " error=" << bpnn.error << endl;
  }
  bpnn.writetrain();
  cout << "trainning complete..." << endl;
  return true;
}

std::string encode_decode::encode(std::string input)
{
  return "";
}
std::string encode_decode::decode(std::string input)
{
  return "";
}

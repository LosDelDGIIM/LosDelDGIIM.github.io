clear;clc;format compact;
% loop-based version:
tic; % starts stopwatch
k = 0;
n = 10^6;
y = zeros(1,n+1); % pre-allocate y
s = 1/n;
for t = 0:s:100
  k = k + 1;
  y(k) = sin(t);
end
time1 = toc % time elapsed since last tic command (in ms)

% vectorized version:
tic;
t = 0:s:100;
y = sin(t);
time2 = toc

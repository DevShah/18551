% Num=Num';
% [y, fs] = wavread('noisy.wav');
% sound(y, fs); %painful
% n = length(y)-1;
% f = -fs/2:fs/n:fs/2;
% figure;
% plot(f,abs(fftshift(fft(y)))); %tone is at 10 kHz
% 
% filt = abs(fftshift(fft(Num, n+1)));
% figure;
% plot(f,filt);
% 
% Y = filter(Num, 1, y);
% figure;
% plot(f,abs(fftshift(fft(Y))));
% 
% sound(Y, fs);

% read wav file
[d,fs,nb]=wavread('filter.wav');
fid=fopen('filter.dat', 'wb');
fwrite(fid, d, 'double');
fclose(fid);
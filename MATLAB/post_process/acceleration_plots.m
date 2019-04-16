% Plot for acceleration vs altitude

max_time = 8598;
% adxl data
acc = dlmread("processed_string.txt", ',', [1 1 max_time 3]);
% bmp altitude data
altitude = dlmread("processed_string.txt", ',', [1 4 max_time 4]);
% mpu data
mpu_acc = dlmread("processed_string.txt", ',', [1 5 max_time 7]);
%%
smooth_x = smooth(acc(300:7000,1), 500,'loess');
smooth_y = smooth(acc(300:7000,2), 500,'loess');
smooth_z = smooth(acc(300:7000,3), 500,'loess');

% while (std(smooth_x) > 1 && std(smooth_y) > 1 && std(smooth_z) > 1) 
%    smooth_x = sgolayfilt(smooth_x, 2, 19);
%    smooth_y = sgolayfilt(smooth_y, 2, 19);
%    smooth_z = sgolayfilt(smooth_z, 2, 19);
% end

acceleration = sqrt((smooth_x).^2 + (smooth_y).^2 + (smooth_z).^2);

figure()
hold on
line([0.82 1.02],[13900 13900],'LineWidth',1)
plot(acceleration, altitude(300:7000), '-r');
hold off
xlim([0.82 1.02]);
xlabel({"\fontsize{14}Acceleration (g)"}, 'FontSize', 14);
ylabel("\fontsize{14}Altitude (m)", 'FontSize', 14);
legend("\fontsize{12}Peak Accleration at 13900 m");
title("\fontsize{16}Max Acceleration vs Altitude");
print("MaxAcceleration", "-dpng", "-r300");

%% Smoothed Acceleration Minus Non Smoothed

max_time = 10500;
time = dlmread("parsed_data_final.csv", ',', [1 0 max_time 0]);
acc = dlmread("parsed_data_final.csv", ',', [1 1 max_time 3]);
mpu_acc = dlmread("parsed_data_final.csv", ',', [1 9 max_time 11]);
altitude = dlmread("parsed_data_final.csv", ',', [1 5 max_time 5]);

% smooth acceleration plots
avg_acc = (acc(:,:) + mpu_acc(:,:))./2.0;
smooth_x = smooth(avg_acc(:,1), 10,'loess');
smooth_y = smooth(avg_acc(:,2), 10,'loess');
smooth_z = smooth(avg_acc(:,3), 10,'loess');

mag_smooth = sqrt( (smooth_x).^2 + (smooth_y).^2 + (smooth_z).^2 );
mag_unsmoothed = sqrt( (avg_acc(:,1)).^2 + (avg_acc(:,2)).^2 + (avg_acc(:,3)).^2 );

difference_smooth_coarse = smooth(mag_unsmoothed - mag_smooth, 5,'loess');
difference_smooth = smooth(mag_unsmoothed - mag_smooth, 50,'loess');
% difference_smooth(difference_smooth < 0.5 & difference_smooth > -0.5) = 0;

hold on
% plot(time, mag_smooth, '-b');

% flight ascencsion
ax1 = subplot(2,1,1);
plot(difference_smooth(500:8000), altitude(500:8000), '-b', 'LineWidth',1);
xlim([-.25 .25]);
title("\fontsize{16}Difference in Smoothed vs. Unsmoothed Acceleration vs. Altitude on Ascent");
ylabel("\fontsize{14}Altitude (m)");
xlabel("\fontsize{14}Acceleration Difference (g)");

ax2 = subplot(2,1,1);
subplot(2,1,2);
difference_smooth = smooth(difference_smooth, 200,'loess');
plot(difference_smooth(8000:max_time), altitude(8000:max_time), '-r', 'LineWidth',2);
line([-0.05 0.45],[18007 18007], 'LineWidth',1);
line([-0.05 0.45],[10700 10700],'LineWidth',1);
xlim([-.05 .45]);
title("\fontsize{16}Difference in Smoothed vs. Unsmoothed Acceleration vs. Altitude on Descent");
ylabel("\fontsize{14}Altitude (m)");
xlabel("\fontsize{14}Acceleration Difference (g)");
hold off
print("AccelerationDifferenceSmoothed", "-dpng", "-r300");
% max value is 0.405 at  index 8468 altitude 18007 m 


%% start dropping in altitude around 22000 
plot(1:max_time, altitude);


% Solve an Input-Output Fitting problem with a Neural Network
% Script generated by Neural Fitting app
% Created 13-Feb-2018 00:16:50
% Significantly Changed by Om Soni to process data, 
% configure the network 

% Step1: Load and preprocess the data
x0 = readDataFile('MultiFontCharInput.txt');
t0 = readDataFile('MultiFontCharOutput.txt');

xtr0 = cell2mat(struct2cell(x0))
ttr0 = cell2mat(struct2cell(t0))

xtr = reshape(xtr0, 14,78);
ttr = reshape(ttr0, 26,78);

x1 = readDataFile('MultiFontCharInputTestData.txt');
t1 = readDataFile('MultiFontCharOutputTestData.txt');

xte0 = cell2mat(struct2cell(x1))
tte0 = cell2mat(struct2cell(t1))

xte = reshape(xte0, 14,78);
tte = reshape(tte0, 26,78);


x = horzcat(xtr,xte);
t = horzcat(ttr, tte);

% STEP 2: Determine Network Arhitecture

% STEP 3: Build and Configure a MLP network
% Choose a Training Function
% 'trainlm' is usually fastest.
% 'trainbr' takes longer but may be better for challenging problems.
% 'trainscg' uses less memory. Suitable in low memory situations.
trainFcn = 'trainscg' % 'trainscg';  % Scaled conjugate gradient backpropagation.

% Create a Pattern Recognition Network
hiddenLayerSize = 20;
net = patternnet(hiddenLayerSize, trainFcn);

% Choose Input and Output Pre/Post-Processing Functions
% For a list of all processing functions type: help nnprocess
net.input.processFcns = {'removeconstantrows','mapstd', 'mapminmax'};

% Setup Division of Data for Training, Validation, Testing
% For a list of all data division functions type: help nndivision
net.divideFcn = 'divideind';  % Divide data randomly
net.divideMode = 'sample';  % Divide up every sample
net.divideParam.trainInd = 1:78;  % 1:116;
net.divideParam.valInd = 79:117;
net.divideParam.testInd = 118:156;
net.trainParam.lr = 0.2;
net.layers{1}.transferFcn = 'logsig';

% Choose a Performance Function
% For a list of all performance functions type: help nnperformance
net.performFcn = 'crossentropy';  % Cross-Entropy

% Choose Plot Functions
% For a list of all plot functions type: help nnplot
net.plotFcns = {'plotperform','plottrainstate','ploterrhist', ...
    'plotconfusion', 'plotroc'};

% STEP 4: Training and Testing the network
% Train the Network
[net,tr] = train(net,x,t);

plotperf(tr);

% Test the Network
y = net(x);
e = gsubtract(t,y);
performance = perform(net,t,y)
tind = vec2ind(t);
yind = vec2ind(y);
percentErrors = sum(tind ~= yind)/numel(tind);

% Recalculate Training, Validation and Test Performance
trainTargets = t .* tr.trainMask{1};
valTargets = t .* tr.valMask{1};
testTargets = t .* tr.testMask{1};
trainPerformance = perform(net,trainTargets,y)
valPerformance = perform(net,valTargets,y)
testPerformance = perform(net,testTargets,y)

% View the Network
view(net)

% Plots
% Uncomment these lines to enable various plots.
figure, plotperform(tr)
%figure, plottrainstate(tr)
%figure, ploterrhist(e)
%figure, plotconfusion(t,y)
figure, plotroc(t,y)

% Deployment
% Change the (false) values to (true) to enable the following code blocks.
% See the help for each generation function for more information.
if (false)
    % Generate MATLAB function for neural network for application
    % deployment in MATLAB scripts or with MATLAB Compiler and Builder
    % tools, or simply to examine the calculations your trained neural
    % network performs.
    genFunction(net,'myNeuralNetworkFunction');
    y = myNeuralNetworkFunction(x);
end
if (false)
    % Generate a matrix-only MATLAB function for neural network code
    % generation with MATLAB Coder tools.
    genFunction(net,'myNeuralNetworkFunction','MatrixOnly','yes');
    y = myNeuralNetworkFunction(x);
end
if (false)
    % Generate a Simulink diagram for simulation or deployment with.
    % Simulink Coder tools.
    gensim(net);
end

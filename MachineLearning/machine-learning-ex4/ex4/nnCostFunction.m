function [J grad] = nnCostFunction(nn_params, ...
                                   input_layer_size, ...
                                   hidden_layer_size, ...
                                   num_labels, ...
                                   X, y, lambda)
%NNCOSTFUNCTION Implements the neural network cost function for a two layer
%neural network which performs classification
%   [J grad] = NNCOSTFUNCTON(nn_params, hidden_layer_size, num_labels, ...
%   X, y, lambda) computes the cost and gradient of the neural network. The
%   parameters for the neural network are "unrolled" into the vector
%   nn_params and need to be converted back into the weight matrices. 
% 
%   The returned parameter grad should be a "unrolled" vector of the
%   partial derivatives of the neural network.
%

% Reshape nn_params back into the parameters Theta1 and Theta2, the weight matrices
% for our 2 layer neural network
Theta1 = reshape(nn_params(1:hidden_layer_size * (input_layer_size + 1)), ...
                 hidden_layer_size, (input_layer_size + 1));

Theta2 = reshape(nn_params((1 + (hidden_layer_size * (input_layer_size + 1))):end), ...
                 num_labels, (hidden_layer_size + 1));

% Setup some useful variables
m = size(X, 1);
         
% You need to return the following variables correctly 
J = 0;
Theta1_grad = zeros(size(Theta1));
Theta2_grad = zeros(size(Theta2));

% ====================== YOUR CODE HERE ======================
% Instructions: You should complete the code by working through the
%               following parts.
%
% Part 1: Feedforward the neural network and return the cost in the
%         variable J. After implementing Part 1, you can verify that your
%         cost function computation is correct by verifying the cost
%         computed in ex4.m
%
% Part 2: Implement the backpropagation algorithm to compute the gradients
%         Theta1_grad and Theta2_grad. You should return the partial derivatives of
%         the cost function with respect to Theta1 and Theta2 in Theta1_grad and
%         Theta2_grad, respectively. After implementing Part 2, you can check
%         that your implementation is correct by running checkNNGradients
%
%         Note: The vector y passed into the function is a vector of labels
%               containing values from 1..K. You need to map this vector into a 
%               binary vector of 1's and 0's to be used with the neural network
%               cost function.
%
%         Hint: We recommend implementing backpropagation using a for-loop
%               over the training examples if you are implementing it for the 
%               first time.
%
% Part 3: Implement regularization with the cost function and gradients.
%
%         Hint: You can implement this around the code for
%               backpropagation. That is, you can compute the gradients for
%               the regularization separately and then add them to Theta1_grad
%               and Theta2_grad from Part 2.
%

% Re-code y vector

y_rec = zeros(size(y,1), num_labels);
for i=1:size(y,1)
    y_rec(i,y(i)) = 1;
end

% Part1

X = [ones(m, 1) X];

Z_2 = Theta1 * X';
A = sigmoid(Z_2)';

n = size(A,1);

A = [ones(n,1) A];

Z_3 = Theta2 * A';
B = sigmoid(Z_3)';

J = sum(sum(-log(B) .* y_rec - log(ones(size(B)) - B) .* (ones(size(y_rec)) - y_rec))) / m;

Theta1_w = Theta1(:,2:size(Theta1,2));
Theta2_w = Theta2(:,2:size(Theta2,2));
reg_part = lambda / 2 / m * (sum(sum(Theta1_w .^2)) + sum(sum(Theta2_w .^2)));
J = J + reg_part;
% Part1 end ============================


% Part 2

delta3 = zeros(size(B));
delta3 = B - y_rec;

Z_2 = [ones(size(Z_2,2),1) Z_2'];
delta2 =delta3 * Theta2 .* sigmoidGradient(Z_2);
delta2 = delta2(:,2:size(delta2,2));

bdelta2 = delta3' * A;
bdelta1 = delta2' * X;

Theta1_grad = 1 / m * bdelta1 + lambda / m * [zeros(size(Theta1,1), 1) Theta1(:, 2:size(Theta1,2))];
Theta2_grad = 1 / m * bdelta2 + lambda / m * [zeros(size(Theta2,1), 1) Theta2(:, 2:size(Theta2,2))];


% -------------------------------------------------------------

% =========================================================================

% Unroll gradients
grad = [Theta1_grad(:) ; Theta2_grad(:)];


end

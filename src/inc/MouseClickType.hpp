#pragma once

struct MouseClickType {
	int left;
	int right;
	int middle;
	int mouse4;
	int mouse5;

	MouseClickType() : left(0), right(0), middle(), mouse4(0), mouse5(0) {}
};
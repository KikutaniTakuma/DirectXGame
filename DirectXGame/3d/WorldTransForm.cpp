#include "WorldTransform.h"

void WorldTransform::UpdateMatrix() {
	matWorld_.Affin(scale_, rotation_, translation_);

	if (parent_) {
		matWorld_ *= parent_->matWorld_;
	}

	TransferMatrix();
}
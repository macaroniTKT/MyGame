#include"Object.h"
#include "AABB.h"

bool Object::CameraClip(VECTOR pos1, VECTOR pos2, VECTOR pos3, VECTOR pos4) {
	//�J�������O����
	if (!CheckCameraViewClip(pos1)) return true;
	if (!CheckCameraViewClip(pos2)) return true;
	if (!CheckCameraViewClip(pos3)) return true;
	if (!CheckCameraViewClip(pos4)) return true;
	return false;
}
void Object1::Initialize() {
	//���f���ǂݍ���
	Building = MV1LoadModel("Asset/Building/MV1/Tower.mv1");
	Building = MV1DuplicateModel(Building);
	Debri = MV1LoadModel("Asset/Building/MV1/Debris.mv1");
	Debri = MV1DuplicateModel(Debri);

	//�T�C�Y�Z�b�g
	MV1SetScale(Building, VGet(0.3f, 0.3f,0.3f));
	MV1SetPosition(Building,ModelPos);
	MV1SetScale(Debri, VGet(0.3f, 0.3f, 0.3f));
	MV1SetPosition(Debri, ModelPos);

	//4�p�ݒ�(�����̓Q�[�����Őݒ�ς�)
	OLU = VGet(ModelPos.x - MAPLONG / 2, ModelPos.y, ModelPos.z + MAPLONG / 2);
	ORU = VGet(ModelPos.x + MAPLONG / 2, ModelPos.y, ModelPos.z + MAPLONG / 2);
	OLD = VGet(ModelPos.x - MAPLONG / 2, ModelPos.y, ModelPos.z - MAPLONG / 2);
	ORD = VGet(ModelPos.x + MAPLONG / 2, ModelPos.y, ModelPos.z - MAPLONG / 2);
}
void Object1::Finalize() {
	//���f���폜
	MV1DeleteModel(Building);
	MV1DeleteModel(Debri);
}
void Object1::Update() {
	Draw();
	Animation();
}
void Object1::Draw() {

	if (CameraClip(OLU,ORU,OLD,ORD))//�J�������O����
	{
		MV1DrawModel(Building);
		MV1DrawModel(Debri);
	}
}
void Object1::Animation() {
	//�A�j���b�������Z
	 AnimNowTime += 1.0f;
	 //�A�j�����i�񂾂�
	 if (AnimNowTime >= AnimTotalTime)
		 if (isHit)Finalize();//�������Ă�����I������
		 else AnimNowTime = 0.0f;//�������Ă��Ȃ��Ȃ烊�Z�b�g

	 //�A�j���b���ŃR�}����
	 MV1SetAttachAnimTime(Building, AnimAttachIndexB, AnimNowTime);
	 MV1SetAttachAnimTime(Debri, AnimAttachIndexD, AnimNowTime);
}
void Object1::SetAnimation() {
	//�A�j���b�������Z�b�g
	AnimNowTime = 0.0f;
	//�A�j���[�V�����Z�b�g
	AnimAttachIndexB = MV1AttachAnim(Building, 0, -1, false);
	AnimAttachIndexD = MV1AttachAnim(Debri, 0, -1, false);
	AnimTotalTime = MV1GetAttachAnimTotalTime(Debri, AnimAttachIndexD);
	MV1SetAttachAnimTime(Building, AnimAttachIndexB, AnimNowTime);
	MV1SetAttachAnimTime(Debri, AnimAttachIndexD, AnimNowTime);
	MV1SetScale(Debri, VGet(0.5f, 0.5f, 0.5f));
}
////////////////////////////////////////////////////////////////////////////////////////////////
//void Object2::Initialize() {
//	//ModelPos = VGet(1000, 0, 1200);
//	Building = MV1LoadModel("Asset/Building/MV1/Tower.mv1");
//	Building = MV1DuplicateModel(Building);
//	MV1SetScale(Building, VGet(0.3f, 0.3f, 0.3f));
//	MV1SetPosition(Building, ModelPos);
//}
//void Object2::Finalize() {
//	MV1DeleteModel(Building);
//}
//void Object2::Update() {
//	Draw();
//}
//void Object2::Draw() {
//		if (CameraClip(OLU, ORU, OLD, ORD))
//		MV1DrawModel(Building);   // ���f���̕`��
//}
//void Object2::Animation() {
//
//}
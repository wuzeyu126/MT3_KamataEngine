#include "MT3.h"
#include <Novice.h>
#include <cstdint>
#include <imgui.h>

const char kWindowTitle[] = "GC1B_04_ゴ_タクウ";
const int kWindowWidth = 1280;
const int kWindowHeight = 720;

Vector3 cameraRotate{0.26f, 0.0f, 0.0f};
Vector3 cameraTranslate{0.0f, 1.9f, -6.49f};

Vector3 startPointX[11], startPointZ[11], endPointX[11], endPointZ[11];

struct Sphere {
	Vector3 center;
	float radius;
};

Sphere sphere_ = {
    {0.0f, 0.0f, 0.0f},
    1.0f
};

void DrawGrid(const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix);
void DrawSphere(const Sphere& sphere, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color);

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, kWindowWidth, kWindowHeight);


	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///

		Matrix4x4 cameraMatrix = MakeAffineMatrix({1.0f, 1.0f, 1.0f}, cameraRotate, cameraTranslate);
		Matrix4x4 worldMatrix = MakeAffineMatrix({1.0f, 1.0f, 1.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f});
		Matrix4x4 viewMatrix = Inverse(cameraMatrix);
		Matrix4x4 projectionMatrix = MakePerspectiveFovMatrix(0.45f, float(kWindowWidth) / float(kWindowHeight), 0.1f, 100.0f);
		Matrix4x4 viewProjectionMatrix_ = Multiply(worldMatrix, Multiply(viewMatrix, projectionMatrix));
		Matrix4x4 viewportMatrix_ = MakeViewportMatrix(0, 0, float(kWindowWidth), float(kWindowHeight), 0.0f, 1.0f);

		ImGui::Begin("Window");
		ImGui::DragFloat3("cameraRotate", &cameraRotate.x, 0.01f);
		ImGui::DragFloat3("cameraTranslate", &cameraTranslate.x, 0.01f);
		ImGui::DragFloat3("Sphere center", &sphere_.center.x, 0.01f);
		ImGui::DragFloat("Sphere radius", &sphere_.radius, 0.01f);
		ImGui::End();

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		DrawGrid(viewProjectionMatrix_, viewportMatrix_);
		DrawSphere(sphere_, viewProjectionMatrix_, viewportMatrix_, 0xFF0000FF);
		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}

void DrawGrid(const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix) {
	const float kGridHalfWidth = 2.0f;
	const uint32_t kSubdivision = 10;
	const float kGridEvery = (kGridHalfWidth * 2.0f) / float(kSubdivision);

	for (uint32_t xIndex = 0; xIndex <= kSubdivision; ++xIndex) {
		startPointX[xIndex] = {-kGridHalfWidth, 0.0f, kGridHalfWidth - xIndex * kGridEvery};
		endPointX[xIndex] = {kGridHalfWidth, 0.0f, kGridHalfWidth - xIndex * kGridEvery};

		Vector3 startPointX_NDC = Transform(startPointX[xIndex], viewProjectionMatrix);
		Vector3 endPointX_NDC = Transform(endPointX[xIndex], viewProjectionMatrix);

		Vector3 startPointX_Screen = Transform(startPointX_NDC, viewportMatrix);
		Vector3 endPointX_Screen = Transform(endPointX_NDC, viewportMatrix);
		if (xIndex == 5) {
			Novice::DrawLine((int)startPointX_Screen.x, (int)startPointX_Screen.y, (int)endPointX_Screen.x, (int)endPointX_Screen.y, BLACK);
		} else {
			Novice::DrawLine((int)startPointX_Screen.x, (int)startPointX_Screen.y, (int)endPointX_Screen.x, (int)endPointX_Screen.y, 0xAAAAAAFF);
		}
	}

	for (uint32_t zIndex = 0; zIndex <= kSubdivision; ++zIndex) {
		startPointZ[zIndex] = {kGridHalfWidth - zIndex * kGridEvery, 0.0f, -kGridHalfWidth};
		endPointZ[zIndex] = {kGridHalfWidth - zIndex * kGridEvery, 0.0f, kGridHalfWidth};

		Vector3 startPointZ_NDC = Transform(startPointZ[zIndex], viewProjectionMatrix);
		Vector3 endPointZ_NDC = Transform(endPointZ[zIndex], viewProjectionMatrix);

		Vector3 startPointZ_Screen = Transform(startPointZ_NDC, viewportMatrix);
		Vector3 endPointZ_Screen = Transform(endPointZ_NDC, viewportMatrix);

		if (zIndex == 5) {
			Novice::DrawLine((int)startPointZ_Screen.x, (int)startPointZ_Screen.y, (int)endPointZ_Screen.x, (int)endPointZ_Screen.y, BLACK);
		} else {
			Novice::DrawLine((int)startPointZ_Screen.x, (int)startPointZ_Screen.y, (int)endPointZ_Screen.x, (int)endPointZ_Screen.y, 0xAAAAAAFF);
		}
	}
}

void DrawSphere(const Sphere& sphere, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color) {
	const uint32_t kSubdivision = 20;                               // 分割数
	const float kLonEvery = 2.0f * float(PI) / float(kSubdivision); // 経度分割1つ分の角度
	const float kLatEvery = float(PI) / float(kSubdivision);        // 緯度分割1つ分の角度
	// 緯度の方向に分割 -π/2 ~ π/2
	for (uint32_t latIndex = 0; latIndex <= kSubdivision; ++latIndex) {
		float lat = float(-PI) / 2.0f + kLatEvery * latIndex; // 現在の緯度
		// 経度の方向に分割 0 ~ 2π
		for (uint32_t lonIndex = 0; lonIndex <= kSubdivision; ++lonIndex) {
			float lon = lonIndex * kLonEvery; // 現在の経度
			// world座標系でのa,b,cを求める
			Vector3 a = Add(sphere.center, Vector3(sphere.radius * cosf(lat) * cosf(lon), sphere.radius * sinf(lat), sphere.radius * cosf(lat) * sinf(lon)));
			Vector3 b = Add(sphere.center, Vector3(sphere.radius * cosf(lat + kLatEvery) * cosf(lon), sphere.radius * sinf(lat + kLatEvery), sphere.radius * cosf(lat + kLatEvery) * sinf(lon)));
			Vector3 c =
			    Add(sphere.center,
			        Vector3(sphere.radius * cosf(lat + kLatEvery) * cosf(lon + kLonEvery), sphere.radius * sinf(lat + kLatEvery), sphere.radius * cosf(lat + kLatEvery) * sinf(lon + kLonEvery)));
			// a,b,cをScreen座標系まで変換
			Vector3 a_NDC = Transform(a, viewProjectionMatrix);
			Vector3 b_NDC = Transform(b, viewProjectionMatrix);
			Vector3 c_NDC = Transform(c, viewProjectionMatrix);

			Vector3 a_screen = Transform(a_NDC, viewportMatrix);
			Vector3 b_screen = Transform(b_NDC, viewportMatrix);
			Vector3 c_screen = Transform(c_NDC, viewportMatrix);
			// ab, bcで線を引く
			Novice::DrawLine((int)a_screen.x, (int)a_screen.y, (int)b_screen.x, (int)b_screen.y, color);
			Novice::DrawLine((int)b_screen.x, (int)b_screen.y, (int)c_screen.x, (int)c_screen.y, color);
		}
	}
}
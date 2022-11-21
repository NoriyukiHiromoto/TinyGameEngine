//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
#include <windows.h>

#define ATS_WINDOWS
#include <Artemis.hpp>
using namespace Artemis;

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
int32_t WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int32_t)
{
	return Core::Bootup(
		L"Artemis.Sample",	// アプリケーション名
		SizeI(1280, 720),	// スクリーンサイズ
		60,					// フレームレート
		[]					// メイン関数
		{
			auto pDevice = Core::GetGraphicsDevice();

			// シェーダーコード
			constexpr char ShderCode[] = ATS_SHADER_CODE(
				cbuffer CBSceneVS : register(b0) {
					float4x4 mView;
					float4x4 mProj;
					float4x4 mWorld;
				};
				struct Attributes {
					float4 position : Position;
					float4 color : Color;
				};
				struct Varyings {
					float4 color : Color;
					float4 position : SV_Position;
					uint instanceID : SV_InstanceID;
				};
				Varyings Vert(Attributes input) {
					Varyings output = (Varyings)0;
					output.position = mul(mProj, mul(mView, mul(mWorld, input.position)));
					output.color = input.color;
					return output;
				}
				float4 Frag(Varyings i) : SV_TARGET0 {
					return i.color;
				}
			);

			// シェーダーのコンパイル
			const auto pVSCode = Utility::ShaderCompiler::CompileVertexShader("VertexShader", "Vert", ShderCode);
			const auto pPSCode = Utility::ShaderCompiler::CompilePixelShader("PixelShader", "Frag", ShderCode);

			constexpr Graphics::VertexInputLayoutData Layouts[] = {
				{ 0, Graphics::eVertexInputLayoutSemanticType::Position, 0, Graphics::eVertexInputLayoutFormatType::Float3,        -1 },
				{ 0, Graphics::eVertexInputLayoutSemanticType::Color,    0, Graphics::eVertexInputLayoutFormatType::Uint8Normalx4, -1 },
			};
			auto pShader = pDevice->CreateShader(Layouts, ARRAY_COUNT_OF(Layouts), pVSCode, pPSCode);

			// 頂点データ
			struct VertexData
			{
				Vector3 position;
				Color color;
			};

			// コンスタントバッファ
			struct CB_Scene
			{
				Matrix mView;
				Matrix mProj;
				Matrix mWorld;
			};

			// リソース生成
			auto pVB = pDevice->CreateVertexBuffer(sizeof(VertexData) * 4);
			auto pCB = pDevice->CreateConstantBuffer(sizeof(CB_Scene));

			float radian = 0.0f;

			// メインループ
			while (Core::Update())
			{
				// 頂点バッファ更新
				auto pVBData = reinterpret_cast<VertexData*>(pDevice->Map(pVB));
				if (pVBData != nullptr)
				{
					pVBData[0].position = Vector3(-1.0f, +1.0f, 0.0f);
					pVBData[0].color = Color::RED;
					pVBData[1].position = Vector3(+1.0f, +1.0f, 0.0f);
					pVBData[1].color = Color::GREEN;
					pVBData[2].position = Vector3(-1.0f, -1.0f, 0.0f);
					pVBData[2].color = Color::BLUE;
					pVBData[3].position = Vector3(+1.0f, -1.0f, 0.0f);
					pVBData[3].color = Color::GRAY;
					pDevice->Unmap(pVB);
				}

				// コンスタントバッファ
				const auto mView = Math::MatrixUtil::LookAtLH(
					Vector3(0.0f, 1.0f, -5.0f),
					Vector3(0.0f, 0.0f, 0.0f),
					Vector3(0.0f, 1.0f, 0.0f));
				const auto mProj = Math::MatrixUtil::PerspectiveFovLH(
					45.0f,
					(float)pDevice->GetBackBufferSize().W / (float)pDevice->GetBackBufferSize().H,
					0.1f,
					100.0f);
				const auto mWorld = Math::MatrixUtil::Multiply(Math::MatrixUtil::Multiply(
					Math::MatrixUtil::RotationX(radian * 0.8f),
					Math::MatrixUtil::RotationY(radian * 0.6f)),
					Math::MatrixUtil::RotationZ(radian * 0.4f));

				radian += Core::GetSystemInfo()->FrameTime()->DeltaTime();

				auto pCBData = reinterpret_cast<CB_Scene*>(pDevice->Map(pCB));
				if (pCBData != nullptr)
				{
					pCBData->mView = mView;
					pCBData->mProj = mProj;
					pCBData->mWorld = mWorld;
					pDevice->Unmap(pCB);
				}

				// シェーダー設定
				pDevice->SetShader(pShader);
				pDevice->SetConstantBuffer(Graphics::eShaderType::Vertex, 0, pCB);

				// ステート設定
				pDevice->SetBlendState(Graphics::BlendState());
				pDevice->SetRasterizerState(Graphics::RasterizerState());
				pDevice->SetDepthStencilState(Graphics::DepthStencilState());
				// 描画ジオメトリ設定
				pDevice->SetVertexBuffer(0, pVB, sizeof(VertexData), 0);
				// 描画呼び出し
				pDevice->SetPrimitiveTopology(Graphics::ePrimitiveTopology::TriangleStrip);
				pDevice->Draw(4, 1, 0, 0);
			}

			// リソース解放
			ATS_SAFE_RELEASE(pCB);
			ATS_SAFE_RELEASE(pVB);
			ATS_SAFE_RELEASE(pShader);

			return true;
		});
}

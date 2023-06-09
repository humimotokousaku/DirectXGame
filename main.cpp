#include <Windows.h>

// ウィンドウプロシージャ(スライド16)
LRESULT WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LRESULT lparam) {
	// メッセージに応じてゲーム固有の処理を行う
	switch (msg) {
		// ウィンドウが破壊された
	case WM_DESTROY:
		// OSに対して、アプリの終了を伝える
		PostQuitMessage(0);
		return 0;
	}

	// 標準のメッセージ処理を行う
	return DefWindowProc(hwnd, msg, wparam, lparam);
}

// Windowsアプリでのエントリーポイント(main関数)(スライド12)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	// コンソールへの文字表示
	OutputDebugStringA("Hello,DirectX!!\n");

	// ウィンドウサイズ(スライド19)
	const int window_width = 1280; // 横幅
	const int window_height = 720; // 縦幅

	// ウィンドウクラスの設定
	WNDCLASSEX w{};
	w.cbSize = sizeof(WNDCLASSEX);
	w.lpfnWndProc = (WNDPROC)WindowProc;	 // ウィンドウプロシージャを設定
	w.lpszClassName = L"DirectXGame";		 // ウィンドウクラス名
	w.hInstance = GetModuleHandle(nullptr);	 // ウィンドウハンドル
	w.hCursor = LoadCursor(NULL, IDC_ARROW); // カーソル指定

	// ウィドウクラスをOSに登録する
	RegisterClassEx(&w);
	// ウィンドウサイズ｛ X座標 Y座標 横幅 縦幅 ｝
	RECT wrc = { 0,0,window_width,window_height };
	// 自動でサイズを補正する
	AdjustWindowRect(&wrc, WS_OVERLAPPEDWINDOW, false);

	// ウィンドウオブジェクトの作成(スライド20)
	HWND hwnd = CreateWindow(w.lpszClassName,
		L"DirectXGame",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		wrc.right - wrc.left,
		wrc.bottom - wrc.top,
		nullptr,
		nullptr,
		w.hInstance,
		nullptr);

	// ウィンドウを表示状態にする
	ShowWindow(hwnd, SW_SHOW);

	// (スライド24)
	MSG msg{}; // メッセージ

	// DirectX初期化処理 ここから


	// DirectX初期化処理 ここまで

	// ゲームループ(ここにゲームの処理を書いていく)
	while (true) {
		// メッセージがある？
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg); // キー入力メッセージの処理
			DispatchMessage(&msg); // プロシージャにメッセージを送る

		}

		// ×ボタンで終了メッセージが来たらゲームループを抜ける
		if (msg.message == WM_QUIT) {
			break;
		}
		
		// DirectX毎フレーム処理 ここから


		// DirectX毎フレーム処理 ここまで
	}

	// ウィンドウクラスを登録解除
	UnregisterClass(w.lpszClassName, w.hInstance);

	return 0;
}
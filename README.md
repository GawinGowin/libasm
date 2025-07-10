[![Run gtest](https://github.com/GawinGowin/libasm/actions/workflows/test_ci.yml/badge.svg)](https://github.com/GawinGowin/libasm/actions/workflows/test_ci.yml)

# libasm

## 概要

`libasm`は、標準Cライブラリ関数（strlen、strcpy、strcmp、write、read、strdup）をx86-64アセンブリ言語で実装したCライブラリです。包括的なテストスイートを含み、MakeとCMakeの両方のビルドシステムをサポートしています。

## 機能

実装されている関数：
- `ft_strlen` - 文字列の長さを計算
- `ft_strcpy` - 文字列をコピー
- `ft_strcmp` - 文字列を比較
- `ft_write` - ファイルディスクリプタに書き込み（システムコールのラッパー）
- `ft_read` - ファイルディスクリプタから読み取り（システムコールのラッパー）
- `ft_strdup` - mallocを使用した文字列の複製

## ビルド方法

### メインビルドシステム（Make）
プロジェクト要件に準拠したMakefileを使用：
```bash
make          # または make all - libasm.a静的ライブラリをビルド
make clean    # オブジェクトファイルを削除
make fclean   # libasm.aを含むすべてのビルド成果物を削除
make re       # クリーンリビルド（fclean + all）
```

**注意**: Makefileは以下の必須ルールを含みます：
- `$(NAME)`: ライブラリのビルド
- `all`: すべてのターゲットをビルド
- `clean`: オブジェクトファイルのクリーンアップ
- `fclean`: 完全なクリーンアップ
- `re`: 再ビルド

### テスト実行（CMake）
開発効率のためCMakeとGoogle Testを使用：
```bash
make build    # ビルドディレクトリを作成してCMakeを設定
make test     # すべてのテストをビルドして実行（事前にmake buildが必要）
```

**注意**: テストシステムは要件にないため、開発とデバッグの効率化のために追加されています。評価時にはMakefileのみが使用されます。

### 手動CMake使用
```bash
mkdir -p build
cd build
cmake -DCMAKE_VERBOSE_MAKEFILE=ON ..
make
```

詳細なテスト結果は`build/tests/Testing/Temporary/LastTest.log`に出力されます。
出力例やエラーの詳細については、[GitHub Actionsのワークフロー](https://github.com/GawinGowin/libasm/actions)ログやアップロードされたTest-Logs成果物を確認してください。

## アーキテクチャ

### アセンブリ実装
- **ソースファイル**: `src/*.s` - 純粋なx86-64 NASMアセンブリ
- **ヘッダー**: `include/libasm.h` - GCC属性付きの関数プロトタイプ
- **アセンブラ**: NASM（`-f elf64`フォーマット）
- **呼び出し規約**: System V AMD64 ABI

### GCC属性の活用
ヘッダーファイルでは最適化と安全性のためにGCC属性を広範囲に使用：
- `__THROW` - C++例外なし
- `__attribute_pure__` - 純粋関数（副作用なし）
- `__attribute_malloc__` - mallocのような動作
- `__nonnull` - 非nullポインタ要件
- `__wur` - 未使用結果の警告
- `__attr_access` - 静的解析のためのバッファアクセスパターン

### テストアーキテクチャ
- **フレームワーク**: Google Test (GTest)
- **テストファイル**: `tests/test_*.cpp` - 関数ごとの個別テストファイル
- **CMake統合**: `gtest_add_tests`による自動テスト発見

## 開発ワークフロー

1. **アセンブリ開発**: `src/`ディレクトリの`.s`ファイルを編集
2. **ライブラリビルド**: `make`を実行してアセンブリソースをコンパイル
3. **テスト実行**: `make test`を使用して実装を検証
4. **デバッグ**: 詳細出力でのデバッグには`make build`を使用

## ファイル構造

```
libasm/
├── src/                    # アセンブリソースファイル
│   ├── ft_strlen.s
│   ├── ft_strcpy.s
│   ├── ft_strcmp.s
│   ├── ft_write.s
│   ├── ft_read.s
│   └── ft_strdup.s
├── include/
│   └── libasm.h           # 関数プロトタイプとGCC属性
├── tests/                 # Google Testテストファイル
│   ├── test_ft_strlen.cpp
│   ├── test_ft_strcpy.cpp
│   ├── test_ft_strcmp.cpp
│   ├── test_ft_write.cpp
│   ├── test_ft_read.cpp
│   └── test_ft_strdup.cpp
├── docs/                  # 日本語ドキュメント
├── Makefile              # メインビルドファイル
├── CMakeLists.txt        # CMake設定
└── README.md             # このファイル
```

## 技術仕様

- **アーキテクチャ**: x86-64
- **アセンブリ構文**: Intel構文（NASM）
- **呼び出し規約**: System V AMD64 ABI
- **レジスタ保護**: 呼び出し元保存レジスタを適切に保護
- **エラーハンドリング**: 標準Cライブラリ規約に準拠（errno設定）

## プロジェクト要件

### 必須要件
- **アセンブリ言語**: 64ビットアセンブリ（x86-64）
- **アセンブラ**: NASM（Netwide Assembler）
- **構文**: Intel構文（AT&T構文は不可）
- **ファイル形式**: `.s`ファイル（インラインアセンブリは不可）
- **呼び出し規約**: System V AMD64 ABI
- **コンパイルフラグ**: `-no-pie`フラグの使用は禁止

### ビルドシステム
- **メインビルド**: Makefile（プロジェクト要件に準拠）
- **テストビルド**: CMake + Google Test（開発効率のため）

### 実装要件
- **ライブラリ名**: `libasm.a`
- **エラーハンドリング**: システムコールエラーの適切な処理
- **errno設定**: `extern ___error`または`errno_location`を使用
- **メモリ管理**: `ft_strdup`では`malloc`の呼び出しが許可

### 開発環境
- NASM（Netwide Assembler）
- GCC（GNU Compiler Collection）
- CMake 3.25.1以上
- Google Test（テスト実行時、自動的にフェッチされます）

## 注意事項

### プロジェクト要件への準拠
- **予期しない終了の禁止**: セグメンテーションフォルト、バスエラー、ダブルフリーなどの予期しない終了は未定義動作以外では禁止
- **Makefileの必須ルール**: `$(NAME)`、`all`、`clean`、`fclean`、`re`のルールを含む
- **効率的なビルド**: 必要なファイルのみの再コンパイル/再リンク
- **64ビットアセンブリ**: x86-64アーキテクチャ必須
- **呼び出し規約**: System V AMD64 ABI準拠

### 開発方針
- **テストの推奨**: プロジェクト要件ではないが、開発効率のためテストプログラムを含む
- **エラーハンドリング**: システムコールエラーの適切な処理と`errno`の設定
- **メモリ管理**: `ft_strdup`では`malloc`を使用し、適切なメモリ管理を実施

## CI/CD

### GitHub Actions
プロジェクトは継続的インテグレーションにGitHub Actionsを使用しています：

**ワークフローファイル**: `.github/workflows/test_ci.yml`

**トリガー**:
- `main`ブランチへのpush
- `main`ブランチをターゲットとするプルリクエスト
- 手動ワークフロー実行

**CIパイプライン**:
1. **環境設定**: Ubuntu最新版でNASMをインストール
2. **テスト実行**: `make -s test`を実行（サイレントモード）
3. **成果物アップロード**: 失敗時にテストログをアップロード

**主要機能**:
- 最小限の依存関係（NASMのみ必要）
- 失敗時の自動テストログ収集
- クリーンなCI出力のためのサイレント実行
- 即座の成果物アップロードによるフェイルファスト方式

### CI/CD コマンド
- **手動トリガー**: GitHub Actionsの「Run workflow」ボタンを使用
- **ローカルCI模擬**: `make -s test`でCI環境を再現
- **CI失敗のデバッグ**: GitHub Actionsの成果物でアップロードされたテストログを確認

## ライセンス

このプロジェクトは学習目的で作成されています。

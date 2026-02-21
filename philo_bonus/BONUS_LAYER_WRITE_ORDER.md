# philo_bonus: レイヤー別の理想実装順序

## 前提レイヤー
- Entry: `entry_main.c`
- Setup: `setup_contract.h`, `setup_init.c`
- Parent Runtime: `parent_runtime.c`
- Child Runtime: `child_runtime.c`
- Infra: `infra_semaphore.c`, `infra_time.c`, `infra_utils.c`

## 理想的な「実装順（書く順）」

### 1. Setup契約を先に固定する
- 対象: `setup_contract.h`
- ここで決めるもの:
  - `t_info`, `t_philo`, enum, セマフォ名, 関数プロトタイプ
- 理由:
  - 以降の全ファイルの依存先を最初に固定できる

### 2. Infraの土台を先に作る
- 対象: `infra_time.c`, `infra_semaphore.c`, `infra_utils.c`
- ここで作るもの:
  - 時刻取得/待機、semラッパ、最小ユーティリティ
- 理由:
  - 上位レイヤーが使う共通部品を先に安定化できる

### 3. Setup処理を書く
- 対象: `setup_init.c`
- ここで作るもの:
  - 引数検証、初期化、初期時刻や配列の準備
- 理由:
  - Parent/Child実装前に実行前提を確定できる

### 4. Child Runtimeのコアを書く
- 対象: `child_runtime.c`
- ここで作るもの:
  - eat/sleep/thinkループ、監視連携
- 理由:
  - 「子が何をするか」を先に完成させると親側設計が楽になる

### 5. Child監視と起動順を実装する
- 対象: `child_runtime.c`
- ここで作るもの:
  - 子監視スレッド、死亡判定、子起動手順
- 理由:
  - ルーティンと監視の競合ポイントを子側で閉じ込められる

### 6. Parentの生成/監視を実装する
- 対象: `parent_runtime.c`
- ここで作るもの:
  - fork生成、waitpid監視、死亡時全kill、実行統括
- 理由:
  - 停止戦略を親に一本化して終了制御を安定化できる

### 7. Cleanupを実装する
- 対象: `infra_semaphore.c`
- ここで作るもの:
  - close/unlink、異常系を含む共通後始末
- 理由:
  - すべての終了経路を最後に統合できる

### 8. Infraのログ出力を実装する
- 対象: `infra_utils.c`
- ここで作るもの:
  - 状態文字列化、時刻付きログ出力
- 理由:
  - I/O境界処理をChild Runtimeから分離できる

### 9. Entryで全体を接続する
- 対象: `entry_main.c`
- ここで作るもの:
  - Setup -> Parent Runtime -> Cleanup の接続
- 理由:
  - 各層完成後に接続するとデバッグ範囲を絞れる

### 10. Makefileを最後に確定する
- 対象: `Makefile`
- ここで作るもの:
  - コンパイル対象・依存更新
- 理由:
  - ファイル増減が落ち着いた後に確定するのが最小手戻り

## 実行時の理想処理順（ランタイム順）
1. `setup_init.c`: 引数検証 + 構造体/配列の初期化
2. `parent_runtime.c`: 実行開始、セマフォ初期化、子生成、親監視
3. `child_runtime.c`: 各子で監視者起動 + eat/sleep/think
4. `infra_utils.c`: 状態ログ出力
5. `infra_semaphore.c`: セマフォ後始末(close/unlink)
6. `entry_main.c`: 終了コード返却

## 実装時の優先チェックポイント
- 子が死亡した瞬間に親が全子を止められるか
- `sem_unlink`/`sem_close`/`waitpid` の漏れがないか
- 監視開始前にルーティンが先行しないか
- 異常系でも `infra_semaphore.c` のcleanup導線に必ず到達するか

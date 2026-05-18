*This project has been created as part of the 42 curriculum by kesaitou.*

# Philosophers

## **設計思想（DDD: ドメイン駆動設計 ）**

本リポジトリは **ドメイン駆動設計（Domain-Driven Design / DDD）** の考え方を採用しています。
mandatory と bonus はいずれも「食事する哲学者問題」という同一のドメインを扱っており、
ルール（食事・睡眠・思考・死亡判定・終了条件）は両者で変わりません。
そこで、ドメインの中核ルールを独立したレイヤーに切り出し、外側のレイヤー
（プロセス・スレッドなどの並行プリミティブやI/O）を入れ替えるだけで両実装を成立させる構造にしています。

つまり、mandatory と bonus の本質的な違いは「並行性をどう実現するか」だけであり、
ドメインロジックそのものは共有可能な不変の概念として扱われています。

さらに、レイヤー間の結合を疎に保つために **依存性の注入（Dependency Injection / DI）** を用いています。
domain や application は具体的な同期プリミティブ（ミューテックスやセマフォ）やロギング手段に
直接依存せず、必要な共有状態・ロック・時刻取得・出力先などを `presentation/` 層で組み立てたうえで
構造体（コンテキスト）として外側から渡す形をとっています。
これにより、domain 側のコードを書き換えずに、mandatory（pthread + mutex）と
bonus（process + semaphore）という異なるインフラ実装へ差し替え可能になっています。

ディレクトリは責務（レイヤー）ごとに整理されており、`philo/` と `philo_bonus/` の両方で同じ構造を採っています:

- `presentation/`: エントリポイント、引数のパース、セットアップ、クリーンアップ、依存関係の組み立てと注入
- `application/`: シミュレーションのフロー、モニタリング、オーケストレーション
- `domain/`: 哲学者の振る舞いに関するルール（中核ドメイン、外部依存を持たない）
- `infrastructure/`: 時間、ロギング、同期、低レベル操作（注入される具体実装）
- `include/`: そのターゲットで共有されるパブリックヘッダ

## **概要**

`Philosophers` は、食事する哲学者問題（Dining Philosophers Problem）をテーマにした
42 の並行処理に関する課題です。
C 言語で正しく、レースコンディションのないシミュレーションを構築することを目的としており、
その過程でスレッド、プロセス、ミューテックス、タイミング制御、終了条件の扱い方を学びます。
また、デッドロックやスタベーション、並行処理を安全に協調させるために必要なトレードオフを
実際に手を動かして学ぶ場にもなっています。

本リポジトリには 2 種類の実装が含まれています:

- `philo/`: mandatory パート（POSIX スレッドとミューテックスを使用）
- `philo_bonus/`: bonus パート（プロセスとセマフォを使用）

どちらのプログラムも同じルールセットを受け取ります:

```text
number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

シミュレーションは、哲学者が 1 人でも死亡した時点で停止します。
オプション引数が指定されている場合は、全員が指定回数以上食事を終えた時点でも停止します。

## **使い方**

### 必要環境

- C コンパイラ（`cc` など）
- POSIX スレッドのサポート
- Unix 系の環境

### ビルド

mandatory プログラムのビルド:

```bash
cd philo
make
```

bonus プログラムのビルド:

```bash
cd philo_bonus
make
```

両ディレクトリで利用可能な Makefile ターゲット:

```bash
make
make clean
make fclean
make re
```

### 実行

mandatory バージョン:

```bash
./philo 5 800 200 200
./philo 5 800 200 200 7
```

bonus バージョン:

```bash
./philo_bonus 5 800 200 200
./philo_bonus 5 800 200 200 7
```

引数の意味:

- `number_of_philosophers`: 哲学者およびフォークの数
- `time_to_die`: 哲学者が食事をしないでいられる最大時間（ミリ秒）
- `time_to_eat`: 食事にかかる時間（ミリ秒）
- `time_to_sleep`: 睡眠にかかる時間（ミリ秒）
- `number_of_times_each_philosopher_must_eat`: 任意の終了条件（食事回数）

入力が不正な場合、プログラムは標準エラー出力に `Error` を出力して終了します。

## **参考資料**

このテーマに関連する古典的なリファレンス:

- POSIX スレッド: [`pthread_create(3)`](https://man7.org/linux/man-pages/man3/pthread_create.3.html), [`pthread_mutex_lock(3p)`](https://man7.org/linux/man-pages/man3/pthread_mutex_lock.3p.html)
- POSIX セマフォ: [`sem_open(3)`](https://man7.org/linux/man-pages/man3/sem_open.3.html), [`sem_wait(3)`](https://man7.org/linux/man-pages/man3/sem_wait.3.html)
- 食事する哲学者問題の背景: [Wikipedia - 食事する哲学者の問題](https://ja.wikipedia.org/wiki/%E9%A3%9F%E4%BA%8B%E3%81%99%E3%82%8B%E5%93%B2%E5%AD%A6%E8%80%85%E3%81%AE%E5%95%8F%E9%A1%8C)
- タイミング・プロセス制御: [`gettimeofday(2)`](https://man7.org/linux/man-pages/man2/gettimeofday.2.html), [`fork(2)`](https://man7.org/linux/man-pages/man2/fork.2.html), [`waitpid(2)`](https://man7.org/linux/man-pages/man2/waitpid.2.html)

本リポジトリのドキュメントにおける AI の利用について:

- AI は主に、コードリファクタリングの補助、および本リポジトリで採用しているアーキテクチャを
  学習・適用するうえで適したディレクトリ構造の提案に利用しています。
- README の文言・構成についても、42 の `Readme Requirements` に沿うように
  AI を活用して整えています。
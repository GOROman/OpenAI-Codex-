# OpenAI-Codex-
OpenAIのCodexを試したいリポジトリ。サンプルプログラムでは「Hello, Work! 無職万歳！」を表示します。

## Markov Chain Example
`markov_chain.c` はシャノンの「通信の数学的理論」で用いられるようなマルコフ連鎖を簡単に再現したものです。遷移確率行列を使って文字列を生成します。

## Japanese Word Markov Chain Example
`word_markov_chain.c` は指定された単語群からマルコフ連鎖を構成し、ランダムに文を生成します。
コンパイルして実行すると、たとえば「あなたのメロンを食べます」のような文章が表示されます。

## Rebel School Adventure
`rebel_game.c` は反抗的な生徒となって夜の校舎を暴れ回るテキストゲームです。
以下のようにコンパイルして実行できます。

```
$ gcc -std=c11 -Wall -Wextra rebel_game.c -o rebel_game
$ ./rebel_game
```
## Puyo Puyo Clone
`puyopuyo/index.html` をブラウザで開くと、シンプルなぷよぷよ風ゲームを遊べます。
矢印キーで操作してください。

## Hなじゃんけん Game
`h_janken.c` はちょっと不良っぽいノリのじゃんけんゲームです。コンパイルして実行すると、
大人向けの台詞と共に勝敗が表示されます。

```bash
gcc -std=c11 -Wall -Wextra -o h_janken h_janken.c
./h_janken
```

## 崩撃雲身双虎掌 Training
`akira_spod/index.html` をブラウザで開くと、アキラの必殺技「崩撃雲身双虎掌」を練習できます。
指示に従って矢印キーと P・G キーを押し、コンボを決めましょう。

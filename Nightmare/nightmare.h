
/*
  
  マルチプラットフォーム対応させるゲーム用ライブラリ

  none: 作者の許可無くこれらを使用する行為は一切認めていません。
        [追記] 使用するプロジェクトに作者を参加させる条件の元で使用出来ます。
  
  author: iron_dice

*/

/*
  
  出来る事一覧
  
  - 描写処理サポート
  - 音声処理サポート
  - 入力処理サポート

  - ベクトル処理のサポート
  - アプリケーション処理のサポート

 */

/*

  命名規則:

  #define を使った定義には NM から始まる事
  例: NM_EXAMPLE_DEFINE

  インクルードブロックには __NM_{ヘッダーファイル名}_H__ を使った定義をする事

  ライブラリに関わる名前空間は全て ::dream::~ から始まる事

 */

#ifndef __NM_NIGHTMARE_H__
#define __NM_NIGHTMARE_H__

// 自前ライブラリのヘッダー展開
#include "core\device.h"
#include "core\application.h"
#include "core\input.h"
#include "core\debug.h"
#include "core\vector.h"
#include "core\types.h"
#include "core\project.h"

#endif // __NM_NIGHTMARE_H__

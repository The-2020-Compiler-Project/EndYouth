＜operator_plus＞            ->       +｜-                                                                                                                                     // 加减
＜oprator_mul＞              ->       *｜/                                                                                                                                     // 乘除
＜relational＞               ->       <｜<=｜>｜>=｜!=｜==                                                                                                                      // 关系运算
＜letter＞                   ->       ＿｜a｜．．．｜z｜A｜．．．｜Z                                                                                                               // 字母
＜number＞                   ->       ０｜＜nonezero＞                                                                                                                          // 数字
＜nonezero＞                 ->       １｜．．．｜９                                                                                                                             // 非零数字
＜chars＞                    ->       '<operator_plus>'｜'＜oprator_mul＞'｜'＜letter＞'｜'＜number＞'                                                                            // 字符
＜char_str＞                 ->       "｛十进制编码为32,33,35-126的ASCII字符｝"                                                                                                    // 字符串
＜program＞                  ->      ［＜constants_declare＞］［＜var_declare＞］{＜value_function＞|＜novalue_function＞}＜main_function＞                                         // 程序
＜constants_declare＞        ->       const＜constants_df＞;{ const＜constants_df＞;}                                                                                            // 常量说明
＜constants_df＞             ->       int＜identifier＞＝＜in t＞{,＜identifier＞＝＜int_number＞}                                                                                // 常量定义
                                     | char＜identifier＞＝<chars＞{,＜identifier＞＝＜chars＞}
＜unsigned_int＞             ->       ＜nonezero＞｛＜number＞｝| 0                                                                                                              // 无符号整数
＜int_number＞               ->      ［＋｜－］＜unsigned_int＞                                                                                                                  // 整数
＜identifier＞               ->       ＜letter＞｛＜letter＞｜＜number＞｝                                                                                                        // 标识符
＜head_state＞               ->       int＜identifier＞ |char＜identifier＞                                                                                                      // 声明头部
＜var_declare＞              ->       ＜var_df＞;{＜var_df＞;}                                                                                                                  // 变量说明
＜var_df＞                   ->       ＜tyoe_identifier＞(＜identifier＞|＜identifier＞'['＜unsigned_int＞']'){,(＜identifier＞|＜identifier＞'['＜unsigned_int＞']' )}                                // 变量定义
                                                                                                                                                                              // ＜unsigned_int＞表示数组元素的个数，其值需大于0
＜type_identifier＞          ->        int | char                                                                                                                              // 类型标识符
＜value_function＞           ->       ＜head_state＞'('＜parameter_List＞')' '{'＜compound_sentence＞'}'                                                                         // 有返回值函数定义
＜novalue_function＞         ->       void＜identifier＞'('＜parameter_list＞')''{'＜compound_sentence＞'}'                                                                      // 无返回值函数定义
＜compound_sentence＞        ->      ［＜constants_declare＞］［＜var_declare＞］＜sentence_list＞                                                                                 // 符合语句
＜parameter_list＞           ->       ＜tyoe_identifier＞＜identifier＞{,＜tyoe_identifier＞＜identifier＞}| ＜空＞                                                                // 参数表
＜main_function＞            ->       void main‘(’‘)’ ‘{’＜compound_sentence＞‘}’                                                                                               // 主函数
＜expresion＞                ->       ［＋｜－］＜item＞{＜operator_plus＞＜item＞}                            // [+|-]只作用于第一个<项>                                             // 表达式
＜item＞                     ->       ＜factor＞{＜operator_mul＞＜factor＞}                                                                                                     // 项
＜factor＞                   ->       ＜identifier＞｜＜identifier＞'['＜expresion＞']'|'('＜expresion＞')'｜＜int_number＞|＜chars＞｜＜value_function_call＞                       // 因子
＜sentence＞                 ->       ＜conditonal_sentence＞｜＜loop_sentence＞| '{'＜sentence_list＞'}'| ＜value_function_call＞;                                                // 语句
                                      |＜novalue_function_call＞;｜＜assignment_sentence＞;｜＜read_sentence＞;｜＜write_sentence＞;｜＜null＞;|＜return_sentence＞;
＜assignment_sentence＞      ->       ＜identifier＞＝＜expresion＞|＜identifier＞'['＜expresion＞']'=＜expresion＞                                                                // 赋值语句
＜conditonal_sentence＞      ->       if '('＜condition＞')'＜sentence＞［else＜sentence＞］                                                                                       // 条件语句
＜condition＞                ->       ＜expresion＞＜relational＞＜expresion＞                       // 整型expresion之间才能进行关系运算                                             // 条件
                                     ｜＜expresion＞                                               // expresion为整型，其值为0条件为假，值不为0时条件为真                                             
＜loop_sentence＞            ->        while '('＜conditon＞')'＜sentence＞| do＜sentence＞while '('＜condition＞')' |for'('＜identifier＞＝＜expresion＞;＜condition＞;＜identifier＞＝＜identifier＞(+|-)＜step_size＞')'＜sentence＞                               // 循环语句
＜step_size＞                ->       ＜unsigned_int＞                                                                                                                          // 步长
＜value_function_call＞      ->       ＜identifier＞'('＜value_parameter＞')'                                                                                                   // 有返回值函数调用语句
＜novalue_function_call＞    ->       ＜identifier＞'('＜valueparameter＞')'                                                                                                     // 无返回值函数调用语句
＜value_parameter＞          ->       ＜expresion＞{,＜expresion＞}｜＜numm＞                                                                                                     // 值参数表
＜sentence_list＞            ->      ｛＜sentence＞｝                                                                                                                            // 语句列
＜read_sentence＞            ->       scanf '('＜identifier＞{,＜identifier＞}')'                                                                                                // 读语句
＜write_sentence＞           ->       printf '(' ＜char_str＞,＜expresion＞ ')'| printf '('＜char_str＞ ')'| printf '('＜expresion＞')'                                           // 写语句
＜return_sentence＞          ->       return['('＜expresion＞')']                                                                                                               // 返回语句
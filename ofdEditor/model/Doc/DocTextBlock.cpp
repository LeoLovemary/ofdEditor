#include "DocTextBlock.h"
#include "Doc/DocParagraph.h"

#include <QTextCursor>
#include <QPalette>
#include <QMenu>
#include <QAction>
#include <QString>
#include <QDebug>

DocTextBlock::DocTextBlock(QWidget *parent)
    :QTextEdit(parent)
{
//    QTextCursor cursor(this->textCursor());
//    cursor.insertText(tr("testsesetstsetestes"));

//    this->setBackgroundRole(QPalette::Dark);
    this->init();   // 调用初始化函数

}

DocTextBlock::~DocTextBlock()
{

}

/**
 * @Author Chaoqun
 * @brief  设置文本内容
 * @param  QString str
 * @return void
 * @date   2017/05/20
 */
void DocTextBlock::setContent(QString str)
{
    QTextCursor cursor(this->textCursor());
    cursor.insertText(str);
}

/**
 * @Author Chaoqun
 * @brief  用来合并格式
 * @param  const QTextCharFormat &format
 * @return void
 * @date   2017/05/20
 */
void DocTextBlock::mergeFormatOnWordOrSelection(
        const QTextCharFormat &format)
{
    QTextCursor cursor = this->textCursor(); // 新建光标
    if(!cursor.hasSelection())
    {
        // 如果没有选择文字段落
        cursor.select(QTextCursor::WordUnderCursor);
        qDebug() << "cursor has no selection!";
    }
    cursor.mergeCharFormat(format);         // 合并光标下的 QTextCharFormat
    this->mergeCurrentCharFormat(format);   // 合并当前的 QTextCharFormat

}

/**
 * @Author Chaoqun
 * @brief  当前CharFormat样式发上改变的响应函数，
 *         当增加了一个字体控制的widget时，可以使用
 * @param  const QTextCharFormat &format
 * @return void
 * @date   2017/05/21
 */
void DocTextBlock::currentCharFormatChangedEvent(
        const QTextCharFormat &format)
{

}

/**
 * @Author Chaoqun
 * @brief  光标位置发生改变时的响应函数
 * @param  void
 * @return void
 * @date   2017/05/21
 */
void DocTextBlock::cursorPositionChangedEvent()
{
//    qDebug() << "Cursor Position Changed!";
}

/**
 * @Author Chaoqun
 * @brief  文字加粗
 * @param  void
 * @return void
 * @date   2017/05/20
 */
void DocTextBlock::textBold()
{
    QTextCharFormat fmt;
    QTextCharFormat currentFormat = this->currentCharFormat();      // 当前选择文字的样式
    fmt.setFontWeight(currentFormat.fontWeight() != QFont::Bold ?   // 设置粗细
                          QFont::Bold : QFont::Normal);

    mergeFormatOnWordOrSelection(fmt);      // 合并格式

}

/**
 * @Author Chaoqun
 * @brief  设置下划线
 * @param  void
 * @return void
 * @date   2017/05/21
 */
void DocTextBlock::textUnderline()
{
    QTextCharFormat fmt;
    QTextCharFormat currentFormat = this->currentCharFormat();      // 当前选择文字的样式
    if(currentFormat.fontUnderline())
    {
        fmt.setFontUnderline(false);
    }
    else
    {
        fmt.setFontUnderline(true);
    }
//    fmt.setFontUnderline(currentFormat.FontUnderline()?false:true);

    mergeFormatOnWordOrSelection(fmt);      // 合并格式
}

/**
 * @Author Chaoqun
 * @brief  设置斜体
 * @param  void
 * @return void
 * @date   2017/05/21
 */
void DocTextBlock::textItalic()
{
    QTextCharFormat fmt;
    QTextCharFormat currentFormat = this->currentCharFormat();      // 当前选择文字的样式
    fmt.setFontItalic(currentFormat.fontItalic() == true?                  // 设置斜体
                          false:true);

    mergeFormatOnWordOrSelection(fmt);      // 合并格式
}

/**
 * @Author Chaoqun
 * @brief  显示右键菜单
 * @param  QContextMenuEvent *event
 * @return void
 * @date   2017/05/20
 */
void DocTextBlock::contextMenuEvent(QContextMenuEvent *event)
{

    this->ContextMenu->exec(event->globalPos());

}

/**
 * @Author Chaoqun
 * @brief  初始化函数
 * @param  void
 * @return void
 * @date   2017/05/20
 */
void DocTextBlock::init()
{
    this->setMinimumSize(15,15);        // 为了正确显示缩放标识

    this->currentTextCharFormat = new QTextCharFormat();        // 初始化


    // 连接当前charFormat改变函数
    connect(this, &DocTextBlock::currentCharFormatChanged,
            this, &DocTextBlock::currentCharFormatChangedEvent);

    // 连接当前光标位置改变事件
    connect(this, &DocTextBlock::cursorPositionChanged,
            this, &DocTextBlock::cursorPositionChangedEvent);

    this->initAcitons();    // 初始化QAction相关
}

/**
 * @Author Chaoqun
 * @brief  初始化按钮 ， QAction
 * @param  void
 * @return 返回值
 * @date   2017/05/21
 */
void DocTextBlock::initAcitons()
{
    // 粗体
    this->actionBold = new QAction(tr("Bold"));
    this->actionBold->setPriority(QAction::LowPriority);
    QFont bold;
    bold.setBold(true);
    this->actionBold->setFont(bold);

    this->connect(this->actionBold,&QAction::triggered,
                  this,&DocTextBlock::textBold);

    // 斜体
    this->actionItalic = new QAction(tr("Italic"));
    this->actionItalic->setPriority(QAction::LowPriority);
    QFont italic;
    italic.setItalic(true);
    this->actionItalic->setFont(italic);

    this->connect(this->actionItalic,&QAction::triggered,
                  this,&DocTextBlock::textItalic);

    // 下划线
    this->actionUnderline = new QAction(tr("Underline"));
    this->actionUnderline->setPriority(QAction::LowPriority);
    QFont underline;
    underline.setUnderline(true);
    this->actionUnderline->setFont(underline);

    this->connect(this->actionUnderline, &QAction::triggered,
                  this,&DocTextBlock::textUnderline);

    // 右键菜单
    this->ContextMenu = createStandardContextMenu();     // 拓展标准菜单
    this->ContextMenu->addAction(this->actionBold);
    this->ContextMenu->addAction(this->actionItalic);
    this->ContextMenu->addAction(this->actionUnderline);
}

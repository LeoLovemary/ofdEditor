#ifndef CT_OUTLINEELEM_H
#define CT_OUTLINEELEM_H

class CT_OutlineElem {
    string title;
    int count;
    bool expanded;
    //++动作
    vector<CT_OutlineElem> outline_elem;
};

#endif // CT_OUTLINEELEM_H

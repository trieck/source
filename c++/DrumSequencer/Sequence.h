#pragma once
class Sequence : public CObject
{
public:
    Sequence();
    ~Sequence() = default;
    void ToggleSub(const CPoint& pt);

    bool GetBeat(int sub, int instrument) const;
    void Clear();
    BYTE GetInstrument(int i) const;

    enum { NINSTRUMENTS = 10 }; // number of instruments
    enum { NBARS = 1 }; // number of bars
    enum { RESOLUTION = 4 }; // number of subdivisions per beat
    enum { BEATS_PER_BAR = 4 }; // number of beats per bar
    enum { NSUBS = RESOLUTION * BEATS_PER_BAR * NBARS }; // number of subdivisions

private:
    bool m_beats[NSUBS][NINSTRUMENTS]{};

DECLARE_SERIAL(Sequence)
    void Serialize(CArchive& ar) override;
};

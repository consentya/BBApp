#include "demod_panel.h"

DemodPanel::DemodPanel(const QString &title,
                       QWidget *parent,
                       const DemodSettings *settings) :
    DockPanel(title, parent)
{
    DockPage *demodPage = new DockPage(tr("Demod Settings"));
    DockPage *triggerPage = new DockPage(tr("Trigger Settings"));

    inputPowerEntry = new AmplitudeEntry(tr("Input Pwr"), 0.0);
    centerEntry = new FrequencyEntry(tr("Center"), 0.0);

    gainEntry = new ComboEntry(tr("Gain"));
    QStringList gain_sl;
    gain_sl << tr("Auto Gain") << tr("Gain 0") << tr("Gain 1") <<
               tr("Gain 2") << tr("Gain 3");
    gainEntry->setComboText(gain_sl);

    attenEntry = new ComboEntry(tr("Atten"));
    QStringList atten_sl;
    atten_sl << tr("Auto Atten") << tr("0 dB") << tr("10 dB")
             << tr("20 dB") << tr("30 dB");
    attenEntry->setComboText(atten_sl);

    decimationEntry = new ComboEntry(tr("Decimation"));
    QStringList decimation_sl;
    decimation_sl << tr("None") << tr("2") << tr("4") << tr("8") <<
                     tr("16") << tr("32") << tr("64") << tr("128");
    decimationEntry->setComboText(decimation_sl);

    bandwidthEntry = new FrequencyEntry(tr("IF BW"), 0.0);
    vbwEntry = new FrequencyEntry(tr("VBW"), 0.0);
    sweepTimeEntry = new TimeEntry(tr("Swp Time"), Time(0.0), MILLISECOND);

    triggerTypeEntry = new ComboEntry(tr("Trigger Type"));
    QStringList triggerType_sl;
    triggerType_sl << tr("No Trigger") << tr("External Trigger");
    triggerTypeEntry->setComboText(triggerType_sl);

    triggerEdgeEntry = new ComboEntry(tr("Trigger Edge"));
    QStringList triggerEdge_sl;
    triggerEdge_sl << tr("Rising Edge") << tr("Falling Edge");
    triggerEdgeEntry->setComboText(triggerEdge_sl);

    triggerAmplitudeEntry = new AmplitudeEntry(tr("Video Trigger Level"), 0.0);

    demodPage->AddWidget(inputPowerEntry);
    demodPage->AddWidget(centerEntry);
    demodPage->AddWidget(gainEntry);
    demodPage->AddWidget(attenEntry);
    demodPage->AddWidget(decimationEntry);
    demodPage->AddWidget(bandwidthEntry);
    demodPage->AddWidget(vbwEntry);
    demodPage->AddWidget(sweepTimeEntry);

    triggerPage->AddWidget(triggerTypeEntry);
    triggerPage->AddWidget(triggerEdgeEntry);
    triggerPage->AddWidget(triggerAmplitudeEntry);

    AddPage(demodPage);
    AddPage(triggerPage);

    updatePanel(settings);

    connect(settings, SIGNAL(updated(const DemodSettings*)),
            this, SLOT(updatePanel(const DemodSettings*)));

    connect(inputPowerEntry, SIGNAL(amplitudeChanged(Amplitude)),
            settings, SLOT(setInputPower(Amplitude)));
    connect(centerEntry, SIGNAL(freqViewChanged(Frequency)),
            settings, SLOT(setCenterFreq(Frequency)));
    connect(gainEntry, SIGNAL(comboIndexChanged(int)),
            settings, SLOT(setGain(int)));
    connect(attenEntry, SIGNAL(comboIndexChanged(int)),
            settings, SLOT(setAtten(int)));
    connect(decimationEntry, SIGNAL(comboIndexChanged(int)),
            settings, SLOT(setDecimation(int)));
    connect(vbwEntry, SIGNAL(freqViewChanged(Frequency)),
            settings, SLOT(setVBW(Frequency)));
    connect(sweepTimeEntry, SIGNAL(timeChanged(Time)),
            settings, SLOT(setSweepTime(Time)));
    connect(triggerTypeEntry, SIGNAL(comboIndexChanged(int)),
            settings, SLOT(setTrigType(int)));
    connect(triggerEdgeEntry, SIGNAL(comboIndexChanged(int)),
            settings, SLOT(setTrigEdge(int)));
    connect(triggerAmplitudeEntry, SIGNAL(amplitudeChanged(Amplitude)),
            settings, SLOT(setTrigAmplitude(Amplitude)));
}

DemodPanel::~DemodPanel()
{

}

void DemodPanel::updatePanel(const DemodSettings *ds)
{
    inputPowerEntry->SetAmplitude(ds->InputPower());
    centerEntry->SetFrequency(ds->CenterFreq());
    gainEntry->setComboIndex(ds->Gain());
    attenEntry->setComboIndex(ds->Atten());
    decimationEntry->setComboIndex(ds->DecimationFactor());
    bandwidthEntry->SetFrequency(ds->Bandwidth());
    vbwEntry->SetFrequency(ds->VBW());
    sweepTimeEntry->SetTime(ds->SweepTime());

    triggerTypeEntry->setComboIndex(ds->TrigType());
    triggerEdgeEntry->setComboIndex(ds->TrigEdge());
    triggerAmplitudeEntry->SetAmplitude(ds->TrigAmplitude());
}

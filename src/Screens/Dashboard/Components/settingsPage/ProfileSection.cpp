#include "ProfileSection.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QPainter>
#include <QPainterPath>

class PlaceholderAvatar : public QFrame {
public:
    PlaceholderAvatar(int size, QWidget* parent = nullptr) : QFrame(parent), m_size(size) {
        setFixedSize(size, size);
    }

protected:
    void paintEvent(QPaintEvent*) override {
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);
        
        painter.setBrush(QColor("#1e293b"));
        painter.setPen(QPen(QColor("#334155"), 2));
        painter.drawRoundedRect(0, 0, m_size, m_size, 20, 20);
        
        painter.setBrush(QColor("#94a3b8"));
        painter.setPen(Qt::NoPen);
        painter.drawEllipse(m_size * 0.35, m_size * 0.25, m_size * 0.3, m_size * 0.3);
        QPainterPath bodyPath;
        bodyPath.moveTo(m_size * 0.2, m_size * 0.85);
        bodyPath.quadTo(m_size * 0.5, m_size * 0.55, m_size * 0.8, m_size * 0.85);
        bodyPath.lineTo(m_size * 0.2, m_size * 0.85);
        painter.drawPath(bodyPath);
        
        painter.setBrush(QColor("#3b82f6"));
        painter.drawEllipse(m_size - 30, m_size - 30, 24, 24);
        painter.setPen(QPen(Qt::white, 2));
        painter.drawLine(m_size - 22, m_size - 18, m_size - 14, m_size - 22);
    }
private:
    int m_size;
};

ProfileSection::ProfileSection(QWidget* parent) : QWidget(parent) {
    auto* mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);

    auto* card = new SettingsCard("Profile Information", this);
    auto* contentLayout = new QHBoxLayout();
    contentLayout->setSpacing(35);

    auto* avatar = new PlaceholderAvatar(130);
    contentLayout->addWidget(avatar);

    auto* inputsLayout = new QVBoxLayout();
    inputsLayout->setSpacing(20);

    // Email Address
    auto* container = new QVBoxLayout();
    container->setSpacing(8);
    auto* lbl = new QLabel("EMAIL ADDRESS");
    lbl->setStyleSheet("color: #64748b; font-size: 10px; font-weight: 800; letter-spacing: 1px;");
    container->addWidget(lbl);
    
    auto* edit = new QLineEdit("admin@kavaro.com");
    edit->setStyleSheet(R"(
        QLineEdit {
            background-color: #0b0f19;
            border: 1px solid #1e293b;
            border-radius: 12px;
            padding: 14px 18px;
            color: #f1f5f9;
            font-size: 14px;
        }
        QLineEdit:focus { border: 1px solid #3b82f6; }
    )");
    container->addWidget(edit);
    inputsLayout->addLayout(container);
    
    contentLayout->addLayout(inputsLayout, 1);
    card->setContent(contentLayout);
    mainLayout->addWidget(card);
}

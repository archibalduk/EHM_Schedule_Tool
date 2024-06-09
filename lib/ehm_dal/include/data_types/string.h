#pragma once

// Application headers
#include "include/data_types/private/abstract_data_type.h"

// Qt headers
class QDataStream;
class QRegularExpression;
#include <QString>
class QVariant;

/*!
 * \brief namespace ehm_dal::data_types
 */
namespace ehm_dal::data_types {

// --- Text string wrapper --- //
/*!
 * \brief The String class acts as a `QString` wrapper for EHM text strings
 */
class String : public AbstractDataType
{
public:
    /*!
     * \brief Default constructor.
     */
    String();
    /*!
     * \brief Constructs the String with `text`.
     * \param text Text string from which the String is to be constructed
     */
    String(const QString &text);
    String(const QString &a, const QString &b, const QVariant &c);
    String(const std::vector<QVariant> &text_list);

    // Comparison
    /*!
     * \brief Compares two Strings. This is the same as `QString::compare()`
     * \param rhs comparator String
     * \param case_sensitivity
     * \return whether the String is lexically higher, lower or equal to `rhs`
     */
    inline qint32 compare(const String &rhs, const Qt::CaseSensitivity case_sensitivity) const
    {
        return get().compare(rhs.get(), case_sensitivity);
    }
    /*!
     * \brief Checks whether two Strings are identical
     * \param rhs comparator String
     * \param case_sensitivity
     * \return whether the Strings are identical
     */
    inline bool isIdenticalTo(const String &rhs, const Qt::CaseSensitivity case_sensitivity) const
    {
        return (get().compare(rhs.get(), case_sensitivity) == 0);
    }
    /*!
     * \brief Returns the string text as a match string suitable for comparing against other match strings.
     * This converts the string to lowercase and removes certain characters and accents.
     */
    QString matchString() const;
    /*!
     * \brief Convenience static function for `QString matchString() const;`.
     * \param text to convert to a match string
     */
    inline static QString toMatchString(const QString &text)
    {
        String str(text);
        return str.matchString();
    }
    /*!
     * \brief Convenience static function for `QString matchString() const;`. Combines `a`, `b` and `c` into a single string.
     * \param a first string
     * \param b second string
     * \param c third string
     * \return 
     */
    inline static QString toMatchString(const QString &a, const QString &b, const QVariant &c)
    {
        String str(a, b, c);
        return str.matchString();
    }
    /*!
     * \brief Convenience static function for `QString matchString() const;`. Combines the elemtns of `text_list` into a single string.
     * \param text_list strings to combine
     * \return 
     */
    inline static QString toMatchString(const std::vector<QVariant> &text_list)
    {
        String str(text_list);
        return str.matchString();
    }

    // File i/o
    /*!
     * \brief Read an array of 8-bit `chars` as a text string and store in the String.
     * \param in `QDataStream` pointing to the char array
     * \param length Lengh of `char` array
     */
    void readCharArray(QDataStream &in, const quint16 length);
    void writeCharArray(QDataStream &in, const quint16 length);

    // Get data
    /*!
     * \brief Returns the current text string.
     * \return the text string
     */
    inline QString get() const { return string_; }
    /*!
     * \brief Returns the number of characters in the current text string.
     * \return the text string length
     */
    inline qsizetype size() const { return string_.size(); }
    /*!
     * \brief Returns the text string in hexidecimal format.
     */
    QString toHex() const;

    // Set data
    /*!
     * \brief Clears the curreny text string.
     */
    inline void clear() { string_.clear(); }

private:
    QString string_;

    // Comparison
    static QRegularExpression accented_characters_;

    // File i/o
    friend QDataStream &operator>>(QDataStream &in, String &data);
    friend QDataStream &operator<<(QDataStream &out, const String &data);

    // Get data
    /*!
     * \brief Returns the current text string (for compatibility with QAbstractTableModel).
     * \return the text string
     */
    inline QVariant value(const qint32 role = Qt::DisplayRole) const override
    {
        Q_UNUSED(role)
        return string_;
    }

    /*!
     * \brief Sets the current text string from `value`.
     * \param value Target text string
     */
    inline void setValue(const QVariant &value) override { string_ = value.toString().trimmed(); }

    // Standard text lengths (mostly for EHM 200x)
    enum ENUM_TEXT_LENGTHS {
        SAV_INDEX_TEXT_LENGTH = 260, // EHM 200x and EHM 1 saved games
        LONG_TEXT_LENGTH = 101,
        STANDARD_TEXT_LENGTH = 51,
        SHORT_TEXT_LENGTH = 26,
        REAL_SHORT_TEXT_LENGTH = 6,
        THREE_LETTER_TEXT_LENGTH = 4,
        SIX_LETTER_TEXT_LENGTH = 7
    };
};

// File i/o
QDataStream &operator>>(QDataStream &in, String &data);
QDataStream &operator<<(QDataStream &out, const String &data);

} // namespace ehm_dal::data_types



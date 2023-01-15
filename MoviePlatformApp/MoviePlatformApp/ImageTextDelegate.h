#include <QTableWidget>
#include <QTableWidgetItem>

#include <QTableView>
#include <QAbstractTableModel>
#include <QStandardItemModel>
#include <QItemSelectionModel>
#include <QStyledItemDelegate>
#include <QPainter>

class ImageTextDelegate : public QStyledItemDelegate
{
public:
	ImageTextDelegate(QObject* parent = nullptr)
		: QStyledItemDelegate(parent)
	{
	}

	void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
	{
		QStyledItemDelegate::paint(painter, option, index);

		// Get the data from the model
		QVariant data = index.data(Qt::DisplayRole);
		if (!data.canConvert<QPixmap>())
			return;

		// Get the image and text from the data
		QPixmap image = qvariant_cast<QPixmap>(data);
		QString text = index.data(Qt::UserRole).toString();

		if (text.length() > 25) {
			text.insert(25, "\n");
		}

		// Calculate the position of the image and text
		QRect rect = option.rect;
		int imageY = rect.top();
		int textY = imageY + image.height();

		// Draw the image and text
		painter->drawPixmap(rect.left(), imageY, image);
		painter->drawText(rect, Qt::AlignLeft | Qt::AlignBottom, text);
	}

	QSize sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const
	{
		//Get the size of the default delegate
		QSize size = QStyledItemDelegate::sizeHint(option, index);

		// Increase the size to fit the image and text
		QVariant data = index.data(Qt::DisplayRole);
		if (data.canConvert<QPixmap>()) {
			QPixmap image = qvariant_cast<QPixmap>(data);
			size.setHeight(size.height() + image.height());
		}

		return size;
	}
};

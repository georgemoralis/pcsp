#include "stdafx.h"
#include "qt4_sysmemviewer.h"

#include "../../hle/modules/sysmem/sysmem.h"
#include "../../hle/kernel/kernel_partition.h"

qt4_SysmemViewer::qt4_SysmemViewer(QWidget *parent)
: QWidget(parent)
{
    ui.setupUi(this);
    ui.sysmemtree->setColumnCount(5);
    QStringList headerlabels;
    headerlabels << "name" << "uid" << "address range" << "size" << "attributes";
    ui.sysmemtree->setHeaderLabels(headerlabels);
    updateViewer();
}

qt4_SysmemViewer::~qt4_SysmemViewer()
{

}
void qt4_SysmemViewer::updateViewer()
{
    KernelPartition *partition = 0;
    for (int i = 1; partition = theKernelObjects.Next(partition); ++i)
    {
        QTreeWidgetItem *partitionitem = new QTreeWidgetItem(ui.sysmemtree);
        partitionitem->setText(0,partition->GetName());
        partitionitem->setText(1,QString("0x%1").arg(partition->GetUid(),0,16));
        partitionitem->setText(2,QString("0x%1 - 0x%2").arg(partition->m_base_address,8,16,QLatin1Char('0')).arg(partition->m_base_address + partition->m_size,8,16,QLatin1Char('0')));
        partitionitem->setText(3,QString("%1").arg(partition->m_size));
        partitionitem->setText(4,QString("0x%1").arg(partition->m_attributes,0,16));
        ui.sysmemtree->insertTopLevelItem(0,partitionitem);

        KernelPartition::PartitionUsedBlockMap::iterator j;
        for (j = partition->m_used_blocks.begin(); j != partition->m_used_blocks.end(); ++j)
        {
            KernelPartitionBlock *block = j->second;
            QTreeWidgetItem *blockitem = new QTreeWidgetItem(partitionitem);
            blockitem->setText(0,block->GetName());
            blockitem->setText(1,QString("0x%1").arg(block->GetUid(),0,16));
            blockitem->setText(2,QString("0x%1 - 0x%2").arg(partition->LowerBound(block),8,16,QLatin1Char('0')).arg( partition->UpperBound(block),8,16,QLatin1Char('0')));
            blockitem->setText(3,QString("%1").arg(block->m_size));
            ui.sysmemtree->insertTopLevelItem(0,blockitem);
        }
    }
}

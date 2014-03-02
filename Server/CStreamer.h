#ifndef CStreamer_h
#define CStreamer_h

#include <Common.h>

#include <vector>
#include <cassert>

#define CELL_SIZE 512

#ifdef USE_3D_STREAMER
#error "3D Streamer is not supported finished"
#endif

class CStreamCell;

class CStreamEntity
{
private:
	CStreamCell * m_pStreamCell = nullptr;
	CVector3 m_vecStreamPosition;

public:
	CStreamEntity();
	~CStreamEntity();

	CStreamCell * GetStreamCell()
	{
		return m_pStreamCell;
	}

	void SetStreamCell(CStreamCell * pCell)
	{
		m_pStreamCell = pCell;
	}

	__forceinline const CVector3& GetStreamPosition() const
	{
		return m_vecStreamPosition;
	}
};

class CStreamCell
{
private:
	const float m_fCellSize = CELL_SIZE;

	CStreamCell * m_pLeftCell = nullptr;
	CStreamCell * m_pTopCell = nullptr;
	CStreamCell * m_pRightCell = nullptr;
	CStreamCell * m_pBottomCell = nullptr;

	Vector2 m_vecBottomLeft;
	Vector2 m_vecTopRight;

	std::vector<CStreamEntity*> m_vecEntities;

	bool m_bIsExtra = false;

#ifdef USE_3D_STREAMER
	CStreamCell * m_pFrontCell = nullptr;
	CStreamCell * m_pBackCell = nullptr;
#endif

	std::vector<CStreamEntity*> m_vecEntities;

public:
	CStreamCell(Vector2 &vecBottomLeft, Vector2 &vecTopRight)
		: m_vecBottomLeft(vecBottomLeft),
		m_vecTopRight(vecTopRight)
	{

	}

	~CStreamCell();


	Vector2 GetBottomLeft()
	{
		return m_vecBottomLeft;
	}

	Vector2 GetTopRight()
	{
		return m_vecTopRight;
	}

	template <typename T>
	void remove(std::vector<T>& vec, size_t pos)
	{
		std::vector<T>::iterator it = vec.begin();
		std::advance(it, pos);
		vec.erase(it);
	}

	void AddEntity(CStreamEntity * pEntity)
	{
		m_vecEntities.push_back(pEntity);
	}

	void RemoveEntity(CStreamEntity * pEntity)
	{
		int i = 0;
		for (auto entity : m_vecEntities)
		{
			if (entity == pEntity)
			{
				remove(m_vecEntities, i);
				return;
			}
			i++;
		}
	}

	__forceinline void SetLeft(CStreamCell * pLeftCell)
	{
		assert(pLeftCell);
		m_pLeftCell = pLeftCell;
	}

	__forceinline void SetTop(CStreamCell * pTopCell)
	{
		assert(pTopCell);
		m_pTopCell = pTopCell;
	}

	__forceinline void SetRight(CStreamCell * pRightCell)
	{
		assert(pRightCell);
		m_pRightCell = pRightCell;
	}

	__forceinline void SetBottom(CStreamCell * pBottomCell)
	{
		assert(pBottomCell);
		m_pBottomCell = pBottomCell;
	}

#ifdef USE_3D_STREAMER
	__forceinline void SetFront(CStreamCell * pFrontCell)
	{
		assert(pFrontCell);
		m_pFrontCell = pFrontCell;
	}

	__forceinline void SetBack(CStreamCell * pBackCell)
	{
		assert(pBackCell);
		m_pBackCell = pBackCell;
	}
#endif

	__forceinline decltype(m_pLeftCell) GetLeft()
	{
		return m_pLeftCell;
	}

	__forceinline decltype(m_pTopCell) GetTop()
	{
		return m_pTopCell;
	}

	__forceinline decltype(m_pRightCell) GetRight()
	{
		return m_pRightCell;
	}

	__forceinline decltype(m_pBottomCell) GetBottom()
	{
		return m_pBottomCell;
	}

#ifdef USE_3D_STREAMER
	__forceinline decltype(m_pFrontCell) GetFront()
	{
		return m_pFrontCell;
	}

	__forceinline decltype(m_pBackCell) GetBack()
	{
		return m_pBackCell;
	}

#endif

	__forceinline bool Contains(const CVector3 &vecPosition)
	{
		if (vecPosition.fX >= m_vecBottomLeft.fX && vecPosition.fX < m_vecTopRight.fX)
		{
			if (vecPosition.fY >= m_vecBottomLeft.fY && vecPosition.fY < m_vecTopRight.fY)
			{
				return true;
			}
		}
		return false;
	}

	__forceinline void SetExtra(bool bExtra)
	{
		m_bIsExtra = bExtra;
	}

	__forceinline bool IsExtra()
	{
		return m_bIsExtra;
	}

	decltype(m_vecEntities) GetEntities()
	{
		return m_vecEntities;
	}

	void GetEntities(decltype(m_vecEntities) &vec)
	{
		for (auto entity : m_vecEntities)
			vec.push_back(entity);
	}


	__forceinline void GetSurroundingSectors(CStreamCell ** pArray)
	{
		memset(pArray, 0, sizeof (pArray)* 8);
		pArray[1] = m_pTopCell;
		pArray[3] = m_pLeftCell;
		pArray[4] = m_pRightCell;
		pArray[6] = m_pBottomCell;
		if (m_pTopCell)
		{
			pArray[0] = m_pTopCell->GetLeft();
			pArray[2] = m_pTopCell->GetRight();
		}
		else
		{
			if (m_pLeftCell) pArray[0] = m_pLeftCell->GetTop();
			if (m_pRightCell) pArray[2] = m_pRightCell->GetTop();
		}
		if (m_pBottomCell)
		{
			pArray[5] = m_pBottomCell->GetLeft();
			pArray[7] = m_pBottomCell->GetRight();
		}
		else
		{
			if (m_pLeftCell) pArray[5] = m_pLeftCell->GetBottom();
			if (m_pRightCell) pArray[7] = m_pRightCell->GetBottom();
		}
	}
};




/*


******************
*       *        *
*	    *        *
*       *        *
******************
*       *        *
*       *        *
*       *        *
******************

*/

#include <functional>

#define WORLD_SIZE 6000.0f

class CStreamer
{
private:
	float m_fStreamDistance = CVAR_GET_INTEGER("streamdistance");

	Vector2 m_vecBottomLeft = Vector2(-WORLD_SIZE, -WORLD_SIZE);
	Vector2 m_vecTopRight = Vector2(WORLD_SIZE, WORLD_SIZE);

	std::vector<CStreamCell*> m_vecCells;
	std::vector<CStreamCell*> m_vecRowStarts;
	std::vector<CStreamCell*> m_vecExtraCells;
public:
	CStreamer()
	{
		CreateCells();
	}
	~CStreamer();

	__forceinline void CreateCells()
	{
		std::vector<CStreamCell*> vecPreviousRow;

		for (float fY = m_vecBottomLeft.fY; fY < m_vecTopRight.fY; fY += CELL_SIZE)
		{
			std::vector<CStreamCell*> vecRow;

			if (vecRow.size() > 0)
				m_vecRowStarts.push_back(*vecRow.begin());

			auto vecPrevRowIt = vecPreviousRow.begin();
			CStreamCell* pPrevCell = nullptr;
			for (float fX = m_vecBottomLeft.fY; fX < m_vecTopRight.fX; fX += CELL_SIZE)
			{
				CStreamCell* pCell = new CStreamCell(Vector2(fX, fY), Vector2(fX + CELL_SIZE, fY + CELL_SIZE));
				if (vecPrevRowIt != vecPreviousRow.end())
				{
					pCell->SetBottom(*vecPrevRowIt);
					(*vecPrevRowIt)->SetTop(pCell);
					vecPrevRowIt++;
				}

				if (pPrevCell)
				{
					pCell->SetLeft(pPrevCell);
					pPrevCell->SetRight(pCell);
				}

				vecRow.push_back(pCell);
				m_vecCells.push_back(pCell);
				pPrevCell = pCell;
			}

			assert(vecPreviousRow.size() == vecRow.size());

			vecPreviousRow = std::move(vecRow);
		}
	}


	__forceinline void DoPulse()
	{

	}

	__forceinline void ConnectCell(CStreamCell * pCell)
	{
		// TODO
		//	float fTop, fBottom;
		//	pCell->GetPosition(fTop, fBottom);

		//	// Connect up our row
		//	pRow->m_pTop = FindRow(fTop + (m_fRowSize / 2.0f));
		//	pRow->m_pBottom = FindRow(fBottom - (m_fRowSize / 2.0f));

		//	// Connect the other rows to us
		//	if (pRow->m_pTop) pRow->m_pTop->m_pBottom = pRow;
		//	if (pRow->m_pBottom) pRow->m_pBottom->m_pTop = pRow;
	}

	__forceinline CStreamCell* FindOrCreateCell(const CVector3 &vecPosition)
	{
		for (const auto &pCell : m_vecCells)
		{
			if (pCell->Contains(vecPosition))
				return pCell;
		}


		// We need a new cell, align it with the others
		float fBottom = float((int)(vecPosition.fY / CELL_SIZE)) * CELL_SIZE;

		if (vecPosition.fY < 0.0f)
			fBottom -= CELL_SIZE;

		// Not sure if this is correct
		auto pCell = new CStreamCell(Vector2(fBottom, fBottom + CELL_SIZE), Vector2(fBottom + CELL_SIZE, fBottom + CELL_SIZE + CELL_SIZE));

		ConnectCell(pCell);

		pCell->SetExtra(true);
		m_vecExtraCells.push_back(pCell);
		return pCell;
	}

	void OnEntityLeaveCell(CStreamEntity * pEntity, CStreamCell * pCell)
	{
		pCell->RemoveEntity(pEntity);

		// TODO: notify affected clients
	}

	void OnEntityEnterCell(CStreamEntity * pEntity, CStreamCell * pCell)
	{
		pCell->AddEntity(pEntity);

		// TODO: notify affected clients
	}

	__forceinline void OnUpdateStreamPosition(CStreamEntity * pEntity)
	{
		auto vecPosition = pEntity->GetStreamPosition();
		auto pCell = pEntity->GetStreamCell();

		// Fail if the Cell is invalid
		assert(pCell);

		// Have we changed cell?
		if (!pCell->Contains(vecPosition))
		{
			OnEntityLeaveCell(pEntity, pCell);
			pCell = FindOrCreateCell(vecPosition);
			pEntity->SetStreamCell(pCell);
			OnEntityEnterCell(pEntity, pCell);
		}
	}

	std::vector<CStreamEntity *> GetConnectedEntites(CStreamEntity * pEntity)
	{
		int iDepth = 0;
		std::vector<CStreamEntity *> m_vecConnectedEntities;
		CStreamCell * pCell = pEntity->GetStreamCell();

#ifdef GET_ALL_CELLS_IN_SYNC_RANGE
		std::function<void(CStreamCell*, CStreamEntity*, decltype(m_vecConnectedEntities)&)> keks = [&](CStreamCell* pCell, CStreamEntity* pEntity, decltype(m_vecConnectedEntities) &output)
		{
			const CVector3 vecPosition = pEntity->GetStreamPosition();

			CStreamCell * pCells[8];
			pCell->GetSurroundingSectors(pCells);
			for (int i = 0; i < 8; ++i)
			{
				if (pCells[i])
				{


					//	0 = TOP_LEFT
					//	1 = TOP
					//	2 = TOP_RIGHT
					//	4 = LEFT
					//	5 = BOTTOM_LEFT
					//	6 = BOTTOM
					//	7 = BOTTOM RIGHT

					pCells[i]->GetEntities(output);
					keks(pCells[i], pEntity, output);
				}
			}
		};

		keks(pCell, pEntity, m_vecConnectedEntities);
#endif

		CStreamCell * pCells[8];
		pCell->GetSurroundingSectors(pCells);
		for (int i = 0; i < 8; ++i)
			pCells[i]->GetEntities(m_vecConnectedEntities);

		return m_vecConnectedEntities; // vector is not copied here, thx to the move semantics, so no performance loss
	}

};


#endif // CStreamer_h
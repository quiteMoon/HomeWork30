import React, { useEffect, useState } from 'react';
import './Characters.css';

const Characters = () => {
  const [characters, setCharacters] = useState([]);
  const [currentPage, setCurrentPage] = useState(1);
  const [charactersPerPage] = useState(10);

  useEffect(() => {
    const fetchCharacters = async () => {
      const response = await fetch('https://thronesapi.com/api/v2/Characters');
      const data = await response.json();
      setCharacters(data);
    };

    fetchCharacters();
  }, []);

  const indexOfLastCharacter = currentPage * charactersPerPage;
  const indexOfFirstCharacter = indexOfLastCharacter - charactersPerPage;
  const currentCharacters = characters.slice(indexOfFirstCharacter, indexOfLastCharacter);

  const paginate = (pageNumber) => setCurrentPage(pageNumber);

  return (
    <div>
      <h1>Game of Thrones Characters</h1>
      <div className="character-grid">
        {currentCharacters.map((character) => (
          <div key={character.id} className="character-card">
            <img src={character.imageUrl} alt={character.fullName} />
            <p>{character.fullName}</p> {/* Текст вирівняний по центру */}
          </div>
        ))}
      </div>
      <Pagination
        charactersPerPage={charactersPerPage}
        totalCharacters={characters.length}
        paginate={paginate}
        currentPage={currentPage}
      />
    </div>
  );
};

const Pagination = ({ charactersPerPage, totalCharacters, paginate, currentPage }) => {
  const totalPages = Math.ceil(totalCharacters / charactersPerPage);

  return (
    <nav className="pagination-nav">
      <button
        onClick={() => paginate(currentPage - 1)}
        disabled={currentPage === 1}
        className="pagination-button"
      >
        &#9664;
      </button>
      <button
        onClick={() => paginate(currentPage + 1)}
        disabled={currentPage === totalPages}
        className="pagination-button"
      >
        &#9654;
      </button>
    </nav>
  );
};

export default Characters;
